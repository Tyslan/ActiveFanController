#include <math.h>
#include <iostream>
#include <syslog.h>
#include <chrono>
#include <fan.hpp>

FanControl::FanControl(int start_fan_temp, int continious_fan_temp, int fan_start_pwm, int fan_max_pwm)
{
    _start_fan_temp = start_fan_temp;
    _continious_fan_temp = continious_fan_temp;
    _fan_start_pwm = fan_start_pwm;
    _fan_max_pwm = fan_max_pwm;

    initialize_temp_pwm_map();
}

int FanControl::calculate_needed_pwm(const double &current_temp)
{
    int pwm = get_pwm_for_temp(current_temp);

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    if (pwm == 0)
    {
        std::chrono::duration<double> elapsed_seconds = now - last_fan_on;
        if (&last_fan_on != nullptr && elapsed_seconds.count() <= 60)
        {
            pwm = _fan_start_pwm;
            is_fan_on = true;
        }
        else
        {
            is_fan_on = false;
        }
    }
    else
    {
        is_fan_on = true;
    }

    if (last_pwm == 0 && pwm > 0)
    {
        last_fan_on = now;
    }

    last_pwm = pwm;
    return pwm;
}

int FanControl::get_pwm_for_temp(const double &temp)
{
    int temperature = std::round(temp);
    if (temperature < _start_fan_temp)
    {
        return 0;
    }
    if (temperature >= _continious_fan_temp)
    {
        return _fan_max_pwm;
    }
    return _lookup[temp];
}

int FanControl::calculate_timeout()
{
    return 5;
}

void FanControl::initialize_temp_pwm_map()
{
    syslog(LOG_DEBUG, "Initializing ratio's");
    for (int i = _start_fan_temp; i < _continious_fan_temp; i++)
    {
        int temperature_range = _continious_fan_temp - _start_fan_temp;
        double temperature_ratio = (i - _start_fan_temp) / (double)temperature_range;

        int pwm_range = _fan_max_pwm - _fan_start_pwm;
        double offset_pwm = temperature_ratio * pwm_range;
        int pwm = (int)std::round(offset_pwm) + _fan_start_pwm;
        _lookup.insert(std::make_pair(i, pwm));
        syslog(LOG_DEBUG, "Temp: %d, pwm: %d", i, pwm);
    }
}