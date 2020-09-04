#include <math.h>
#include "fan.hpp"
#include <iostream>

FanControl::FanControl(int start_fan_temp, int continious_fan_temp, int fan_start_pwm, int fan_max_pwm){
    _start_fan_temp = start_fan_temp;
    _continious_fan_temp = continious_fan_temp;
    _fan_start_pwm = fan_start_pwm;
    _fan_max_pwm = fan_max_pwm;

    for(int i = _start_fan_temp; i < _continious_fan_temp; i++){
        int temperature_range = _continious_fan_temp - _start_fan_temp;
        double temperature_ratio = (i - _start_fan_temp) / (double) temperature_range;

        int pwm_range = _fan_max_pwm - _fan_start_pwm;
        double offset_pwm =  temperature_ratio * pwm_range;
        int pwm = (int) std::round(offset_pwm) + _fan_start_pwm;
        _lookup.insert(std::make_pair(i, pwm));
        std::cout << "temp: " << i << "= "<< pwm <<"\n";
    }
}

int FanControl::calculate_needed_pwm(const int& current_temp){
    if(current_temp < _start_fan_temp){
        return 0;
    }
    if(current_temp >= _continious_fan_temp){
        return _fan_max_pwm;
    }
    return _lookup[current_temp];
}