#include "checkmanager.h"

#include <unistd.h>
#include <iostream>

CheckManager::CheckManager(size_t repeatingTime, const fs::path &checkingDir,
                 EReportType reportType) : _repeatingTime(repeatingTime), _checkingDir(checkingDir)
{
    visitor = std::make_unique<DirVisitor>();
    initWriter(reportType);
}

void CheckManager::run() const
{
    while (true)
    {
        auto rawInfo = visitor->visit(_checkingDir);
        writer->writeReport(rawInfo);
        std::cout << "Запись произведена" << std::endl;
        sleep(_repeatingTime);
    }
}

void CheckManager::initWriter(EReportType reportType)
{
    writer = std::make_unique<JSONWriter>();
}
