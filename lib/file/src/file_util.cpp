#include <sys/stat.h>
#include <string>
#include <filesystem>
#include <iostream>
#include <syslog.h>

#include <file_util.hpp>

bool exists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

std::string find_in_folder(const std::string &path, const std::string &name)
{
    for (const auto &p : std::filesystem::recursive_directory_iterator(path))
    {
        if (!std::filesystem::is_directory(p))
        {
            std::string file_name = p.path().filename();
            if (file_name == name)
            {
                return std::filesystem::absolute(p.path()).string();
            }
        }
    }
    syslog(LOG_ERR, "File: [%s], not found in path: [%s]", name.c_str(), path.c_str());
    return "";
}