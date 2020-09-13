#include <fstream>
#include <string>
#include <syslog.h>

#include <file/inc/file_util.hpp>

#include <thermal.hpp>

ThermalReader::ThermalReader(std::string zone0, std::string zone1)
{
    if (exists(zone0))
    {
        path_zone0 = zone0;
    }
    else
    {
        syslog(LOG_CRIT, "File doesn't exists: %s", zone0.c_str());
        throw "File for zone0 doesn't exists";
    }

    if (exists(zone1))
    {
        path_zone1 = zone1;
    }
    else
    {
        syslog(LOG_CRIT, "File doesn't exists: %s", zone1.c_str());
        throw "File for zone1 doesn't exists";
    }
    syslog(LOG_INFO, "Thermal Reader started.");
}

int ThermalReader::get_temperature_from_file(const std::string &path)
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

double ThermalReader::get_temperature()
{
    int thermal0 = get_temperature_from_file(path_zone0);
    int thermal1 = get_temperature_from_file(path_zone1);

    if (thermal0 > thermal1)
    {
        return thermal0 / 1000.0;
    }
    return thermal1 / 1000.0;
}