#pragma once

#include "checker.h"

#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

/// 
class IReportWriter
{
public:
    /// 
    IReportWriter() = default;
    ///
    virtual ~IReportWriter() = default;

    /// 
    virtual void writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const = 0;
};

/// 
class JSONWriter : public IReportWriter
{
public:
    /// 
    JSONWriter() = default;
    ///
    virtual ~JSONWriter() = default;

    /// 
    virtual void writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const override;

private:
    /// 
    std::string fileType2Str(EFileType type) const;
};