#include <iostream>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds
#include <syslog.h>

#include <config/inc/config.hpp>
#include <thermal/inc/thermal.hpp>
#include <fan/inc/fan.hpp>
#include <pwm/inc/pwm.hpp>

int main(int argc, char *argv[])
{
   std::string path;
   if (argc == 1)
   {
      path = "/etc/afc";
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

   while (true)
   {
      double temp = thermal_reader.get_temperature();
      int pwm = fan_control.calculate_needed_pwm(temp);
      pwm_writer.setPwm(pwm);
      syslog(LOG_DEBUG, "Temp: %.2f, pwm: %d", temp, pwm);
      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   syslog(LOG_NOTICE, "Stopping Active Fan Control");
   closelog();
}