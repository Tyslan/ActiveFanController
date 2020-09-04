#include <iostream>
#include <thread> // std::this_thread::sleep_for
#include <chrono> // std::chrono::seconds

#include "config.hpp"
#include "thermal.hpp"
#include "pwm.hpp"
#include "fan.hpp"

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

   Config config(path);

   ThermalReader thermal_reader(config.get_path_temp_zone0(), config.get_path_temp_zone1());
   FanControl fan_control(config.get_start_fan_temp(), config.get_continious_fan_temp(), config.get_fan_jump_pwm(), config.get_upper_limit_pwm());
   PwmWriter pwm_writer(config.get_path_pwm(), config.get_fan_jump_pwm(), config.get_upper_limit_pwm());

   while (true)
   {
      int temp = thermal_reader.get_temperature();

      int pwm = fan_control.calculate_needed_pwm(temp);
      pwm_writer.setPwm(pwm);
      std::cout << "Temp: " << temp << ", Pwm: " << pwm << "\n";
      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
}