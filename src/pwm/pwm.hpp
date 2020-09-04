#include <string>

class PwmWriter {
    std::string path;
    const int min = 0;
    int fan_jump;
    int max;

    public:
        PwmWriter(std::string path_pwm, int pwm_fan_jump, int pwm_max);
        void setPwm(int value);
};