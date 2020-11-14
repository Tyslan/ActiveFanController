#include <string>

class PwmWriter
{
    std::string path;
    const int min = 0;
    int fan_jump;
    int max;
    int previous_pwm;
    int original_pwm;

public:
    PwmWriter(std::string path_pwm, int pwm_fan_jump, int pwm_max);
    void setPwm(const int &value);
    void close();

private:
    int get_initial_pwm();
    void write(const int &value);
};