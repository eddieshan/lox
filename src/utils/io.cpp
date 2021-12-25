#include <cstddef>
#include <sys/stat.h>

#include "io.h"

using namespace utils;

size_t io::file_size(const char* path)
{
    struct stat file_attr;
    const auto result = stat(path, &file_attr);
    return file_attr.st_size;
    //return result == 0? file_attr.st_size : -1;
}