#include <map>

class FanControl{
    int _start_fan_temp;
    int _continious_fan_temp;
    int _fan_start_pwm;
    int _fan_max_pwm;
    std::map<int,int> _lookup;

    public:
        FanControl(int start_fan_temp, int continious_fan_temp, int fan_start_pwm, int fan_max_pwm);
        int calculate_needed_pwm(const int&  current_temp);
};