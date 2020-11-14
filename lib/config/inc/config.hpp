#include <string>

class Config
{
    std::string zone0;
    std::string zone1;
    std::string pwm_folder;
    std::string pwm_file;
    int pwm_fan_jump;
    int pwm_upper;
    int start_fan_temp;
    int continious_fan_temp;

public:
    Config(std::string config_path);
    std::string get_path_temp_zone0();
    std::string get_path_temp_zone1();
    std::string get_path_pwm();
    int get_fan_jump_pwm();
    int get_upper_limit_pwm();
    int get_start_fan_temp();
    int get_continious_fan_temp();
};