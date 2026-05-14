#include "reportwriter.h"
#include "utils.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

using namespace nlohmann;

void JSONWriter::writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const
{
    json result = json::object();

    for (const auto &[type, path] : rawInfo)
    {
        result[fileType2Str(type)].push_back(path);
    }

    std::string savingPath = Utils::getHomeDir().string() + "/.media_files";
    std::ofstream file(savingPath);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл на запись");
    }
    file << result.dump(2);
}

std::string JSONWriter::fileType2Str(EFileType type) const
{
    switch (type)
    {
    case EFileType::Audio:
        return "audio";
    case EFileType::Image:
        return "images";
    case EFileType::Video:
        return "video";
    default:
        break;
    }

    return {};
}