#include <map>
#include <chrono>

class FanControl
{
    int _start_fan_temp;
    int _continious_fan_temp;
    int _fan_start_pwm;
    int _fan_max_pwm;
    int last_pwm;
    bool is_fan_on;
    std::chrono::system_clock::time_point last_fan_on;
    std::map<int, int> _lookup;

public:
    FanControl(int start_fan_temp, int continious_fan_temp, int fan_start_pwm, int fan_max_pwm);
    int calculate_needed_pwm(const double &current_temp);
    int calculate_timeout();

private:
    void initialize_temp_pwm_map();
    int get_pwm_for_temp(const double &temp);
};