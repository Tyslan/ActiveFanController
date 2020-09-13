#include <fstream>
#include <string>
#include <syslog.h>

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
        syslog(LOG_CRIT, "File doesn't exists: %s", path_pwm.c_str());
        throw "File for pwm doesn't exists";
    }
    fan_jump = pwm_fan_jump;
    max = pwm_max;
    previous_pwm = get_initial_pwm();
    syslog(LOG_INFO, "Pwm Writer started.");
}

int PwmWriter::get_initial_pwm()
{
    std::string line;
    std::ifstream file(path);
    if (file.good())
    {
        getline(file, line);
        return std::stoi(line);
    }
    return 0;
}

void PwmWriter::write(const int &value)
{
    std::ofstream pwm(path);
    pwm << value;
    pwm.close();
    syslog(LOG_INFO, "Written value %d", value);
}

void PwmWriter::setPwm(const int &value)
{
    if (previous_pwm == value)
    {
        return;
    }
    if (value < fan_jump)
    {
        write(min);
    }
    else if (value > max)
    {
        write(max);
    }
    else
    {
        write(value);
    }
    previous_pwm = value;
}