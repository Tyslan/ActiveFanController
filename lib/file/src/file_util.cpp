#include <sys/stat.h>
#include <string>

#include <file_util.hpp>

bool exists(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}