#include "dirvisitor.h"

DirVisitor::DirVisitor()
{
    checker = std::make_unique<MultimediaChecker>();
}

std::unordered_multimap<EFileType, std::string> DirVisitor::visit(const fs::path &root) const
{
    std::unordered_multimap<EFileType, std::string> result;
    for (const auto& entry : fs::recursive_directory_iterator(root)) 
    {
        if (entry.is_directory())
        {
            continue;
        }

        auto path = entry.path();
        if (auto fileType = checker->check(path); fileType != EFileType::None)
        {
            result.insert({fileType, path.string()});
        }
    }

    return result;
}
