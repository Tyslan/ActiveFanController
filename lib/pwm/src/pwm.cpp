#include <fstream>
#include <string>

#include <file/inc/file_util.hpp>

#include <pwm.hpp>

PwmWriter::PwmWriter(std::string path_pwm, int pwm_fan_jump, int pwm_max)
{
    if (exists(path_pwm))
    {
        path = path_pwm;
    }
    else
    {
        throw "File for pwm doesn't exists";
    }
    fan_jump = pwm_fan_jump;
    max = pwm_max;
}

void write(std::string path, int value)
{
    std::ofstream pwm(path);
    pwm << value;
    pwm.close();
}

void PwmWriter::setPwm(int value)
{
    if (value < fan_jump)
    {
        write(path, min);
    }
    else if (value > max)
    {
        write(path, max);
    }
    else
    {
        write(path, value);
    }
}