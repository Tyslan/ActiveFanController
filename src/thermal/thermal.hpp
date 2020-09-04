#include <string>

class ThermalReader
{
    std::string path_zone0;
    std::string path_zone1;

public:
    ThermalReader(std::string path_zone0, std::string path_zone1);
    double get_temperature();
};