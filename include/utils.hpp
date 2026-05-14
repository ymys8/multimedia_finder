#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace Utils
{
/// Получить путь до домашней директории 
inline fs::path getHomeDir()
{
    const char *home = getenv("HOME");
    if (home)
    {
        return home;
    }

    throw std::runtime_error("Не удалось определить домашний каталог");
}
} // namespace Utils