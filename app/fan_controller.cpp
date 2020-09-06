#include <iostream>
#include <fstream>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds
#include <syslog.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <config/inc/config.hpp>
#include <thermal/inc/thermal.hpp>
#include <fan/inc/fan.hpp>
#include <pwm/inc/pwm.hpp>
#include <file/inc/file_util.hpp>

volatile sig_atomic_t stop_flag = 0;
std ::string lock_path = "/var/lock/fanctl.lock";

void set_stop_flag(int sig)
{
   syslog(LOG_DEBUG, "Received sig %d", sig);
   stop_flag = 1;
   syslog(LOG_DEBUG, "Set stop flag to %d", stop_flag);
}

bool create_lock()
{
   if (exists(lock_path))
   {
      syslog(LOG_CRIT, "Couldn't aquire lock.");
      return false;
   }
   else
   {
      int pid = getpid();
      std::ofstream outfile(lock_path);
      outfile << pid << std::endl;
      syslog(LOG_NOTICE, "created lock %s for pid %d", lock_path.c_str(), pid);
      return true;
   }
}

void release_lock()
{
   if (remove(lock_path.c_str()) != 0)
   {
      syslog(LOG_ERR, "Failed to released lock on %s", lock_path.c_str());
   }
   else
   {
      syslog(LOG_NOTICE, "Succesfully released lock.");
   }
}

int main(int argc, char *argv[])
{
   signal(SIGINT, set_stop_flag);
   signal(SIGTERM, set_stop_flag);
   signal(SIGKILL, set_stop_flag);

   std::string path;
   if (argc == 1)
   {
      path = "/etc/afc.conf";
   }
   if (argc == 2)
   {
      path = argv[1];
   }

   //Set our Logging Mask and open the Log
   setlogmask(LOG_UPTO(LOG_DEBUG));
   openlog("active-fan-control", LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
   syslog(LOG_NOTICE, "Starting Active Fan Control");

   Config config(path);

   ThermalReader thermal_reader(config.get_path_temp_zone0(), config.get_path_temp_zone1());
   FanControl fan_control(config.get_start_fan_temp(), config.get_continious_fan_temp(), config.get_fan_jump_pwm(), config.get_upper_limit_pwm());
   PwmWriter pwm_writer(config.get_path_pwm(), config.get_fan_jump_pwm(), config.get_upper_limit_pwm());

   bool running = create_lock();

   while (running)
   {
      if (stop_flag)
      {
         syslog(LOG_INFO, "Received stop signal");
         running = false;
         syslog(LOG_DEBUG, "Set running to %d", running);
      }
      {
         double temp = thermal_reader.get_temperature();
         int pwm = fan_control.calculate_needed_pwm(temp);
         int timeout = fan_control.calculate_timeout();
         pwm_writer.setPwm(pwm);
         syslog(LOG_DEBUG, "Temp: %.2f, pwm: %d", temp, pwm);
         std::this_thread::sleep_for(std::chrono::seconds(timeout));
      }
   }

   release_lock();
   syslog(LOG_NOTICE, "Stopping Active Fan Control");
   closelog();
   return 0;
}