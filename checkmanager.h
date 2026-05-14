#pragma once

#include <cstdint>
#include <filesystem>

#include "dirvisitor.h"
#include "reportwriter.h"

namespace fs = std::filesystem;

///
enum class EReportType : uint8_t
{
    JSON = 0, ///<
    HTTP      ///<
};

///
class CheckManager
{
  public:
    ///
    CheckManager(size_t repeatingTime = 30, const fs::path &checkingDir = "",
                 EReportType reportType = EReportType::JSON);
    ///
    ~CheckManager() = default;

    ///
    void run() const;

  private:
    ///
    void initWriter(EReportType reportType);

    const size_t _repeatingTime; ///<
    fs::path _checkingDir;       ///<

    std::unique_ptr<DirVisitor> visitor;   ///<
    std::unique_ptr<IReportWriter> writer; ///<
};