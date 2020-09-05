#include <string>

class PwmWriter
{
    std::string path;
    const int min = 0;
    int fan_jump;
    int max;
    int previous_pwm = 0;

public:
    PwmWriter(std::string path_pwm, int pwm_fan_jump, int pwm_max);
    void setPwm(int value);

private:
    void write(std::string path, int value);
};