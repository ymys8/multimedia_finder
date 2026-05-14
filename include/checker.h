#pragma once

#include <filesystem>

namespace fs = std::filesystem;

/// 
enum class EFileType : uint8_t
{
    None = 0,   ///< 
    Audio,  ///< 
    Video,  ///< 
    Image   ///< 
};

/// 
class IFileChecker
{
public:
    /// 
    IFileChecker() = default;
    /// 
    virtual ~IFileChecker() = default;

    /// 
    virtual EFileType check(const fs::path &file) const = 0;
};

/// 
class MultimediaChecker : public IFileChecker
{
public:
    /// 
    MultimediaChecker() = default;
    /// 
    ~MultimediaChecker() = default;

    /// 
    virtual EFileType check(const fs::path &file) const override;

};