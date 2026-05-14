#include "checker.h"
#include "utils.hpp"

#include <unordered_map>

namespace
{
    const std::unordered_map<std::string, EFileType> MEDIA_EXTENSIONS = {
        // Audio
        {".mp3", EFileType::Audio}, {".wav", EFileType::Audio}, {".flac", EFileType::Audio},
        {".ogg", EFileType::Audio}, {".aac", EFileType::Audio}, {".m4a",  EFileType::Audio},
        {".opus",EFileType::Audio}, {".wma", EFileType::Audio}, {".aiff", EFileType::Audio},
        {".ape", EFileType::Audio},
        // Video
        {".mp4", EFileType::Video}, {".mkv", EFileType::Video}, {".avi",  EFileType::Video},
        {".mov", EFileType::Video}, {".mpg", EFileType::Video}, {".mpeg", EFileType::Video},
        {".flv", EFileType::Video}, {".webm",EFileType::Video}, {".wmv",  EFileType::Video},
        {".m4v", EFileType::Video}, {".3gp", EFileType::Video},
        // Image
        {".jpg", EFileType::Image}, {".jpeg",EFileType::Image}, {".png",  EFileType::Image},
        {".gif", EFileType::Image}, {".bmp", EFileType::Image}, {".webp", EFileType::Image},
        {".tiff",EFileType::Image}, {".tif", EFileType::Image}, {".svg",  EFileType::Image},
        {".heic",EFileType::Image}, {".raw", EFileType::Image},
    };
}

EFileType MultimediaChecker::check(const fs::path &file) const
{
    auto extension = file.extension().string();
    Utils::toLower(extension);

    auto findIt = MEDIA_EXTENSIONS.find(extension);
    if (findIt == MEDIA_EXTENSIONS.end())
    {
        return EFileType::None;
    }

    return findIt->second;
}