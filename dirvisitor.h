#pragma once

#include "checker.h"

#include <unordered_map>

namespace fs = std::filesystem;

///
class DirVisitor
{
public:
    ///
    DirVisitor();
    ///
    ~DirVisitor() = default;

    ///
    std::unordered_multimap<EFileType, std::string> visit(const fs::path &root) const;

private:
    std::unique_ptr<IFileChecker> checker; ///<
};