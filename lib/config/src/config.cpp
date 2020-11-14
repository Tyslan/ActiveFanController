#include <fstream>
#include <syslog.h>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <file/inc/file_util.hpp>

#include <config.hpp>

Config::Config(std::string config_path)
{
    std::ifstream i(config_path);
    nlohmann::json j;
    i >> j;

    zone0 = j["temp_zone0_path"];
    zone1 = j["temp_zone1_path"];
    pwm_folder = j["pwm_path"];
    pwm_file = j["pwm_file"];
    pwm_fan_jump = j["pwm_fan_jump"];
    pwm_upper = j["pwm_max"];
    start_fan_temp = j["start_fan_temp"];
    continious_fan_temp = j["continious_fan_temp"];
}

std::string Config::get_path_temp_zone0()
{
    return zone0;
}

std::string Config::get_path_temp_zone1()
{
    return zone1;
}

std::string Config::get_path_pwm()
{
    syslog(LOG_DEBUG, "Getting path for %s, %s", pwm_folder.c_str(), pwm_file.c_str());
    std::string path = find_in_folder(pwm_folder, pwm_file);
    if (path.empty())
    {
        throw std::logic_error("pwm path couldn't be found.");
    }
    syslog(LOG_DEBUG, "Found path: %s", path.c_str());
    return path;
}

int Config::get_fan_jump_pwm()
{
    return pwm_fan_jump;
}

int Config::get_upper_limit_pwm()
{
    return pwm_upper;
}

int Config::get_start_fan_temp()
{
    return start_fan_temp;
}

int Config::get_continious_fan_temp()
{
    return continious_fan_temp;
}