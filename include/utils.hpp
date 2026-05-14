#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace Utils
{
inline fs::path getHomeDir()
{
    const char *home = getenv("HOME");
    if (home)
    {
        return home;
    }

    return "";
}
} // namespace Utils