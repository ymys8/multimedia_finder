#pragma once

#include "checkmanager.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>

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

/// Аргументы командной строки
struct CmdArgs
{
    std::string directory;  ///< Директория для обхода
    int interval;           ///< Временной интервал
    EReportType reportType; ///< Тип отчета
};

/// Привести строку к нижнему регистру 
inline void toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
}

/// Парсинг аргументов командной строки
inline CmdArgs parse(int argc, char *argv[])
{
    const std::string howUseUtil = "Как использовать: server -c <путь до конфига> -p <порт сервера>";
    CmdArgs result;
    result.directory = Utils::getHomeDir();
    result.interval = 30;
    result.reportType = EReportType::JSON;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--dir" && i + 1 < argc)
        {
            result.directory = argv[++i];
        }
        else if (arg == "--interval" && i + 1 < argc)
        {
            result.interval = std::stoi(argv[++i]);
            if (result.interval <= 0)
            {
                throw std::invalid_argument("Требуется положительное значение интервала");
            }
        }
        else if (arg == "--report" && i + 1 < argc)
        {
            std::string type = argv[++i];
            toLower(type);

            if (type == "json")
            {
                result.reportType = EReportType::JSON;
            }
            else if (type == "http")
            {
                result.reportType = EReportType::HTTP;
            }
            else
            {
                throw std::invalid_argument("Неизвестный тип отчета: " + type);
            }
        }
        else
        {
            throw std::invalid_argument("Неизвестный аргумент: " + arg);
        }
    }

    return result;
}
} // namespace Utils