#include "dirvisitor.h"

#include <iostream>

DirVisitor::DirVisitor()
{
    checker = std::make_unique<MultimediaChecker>();
}

std::unordered_multimap<EFileType, std::string> DirVisitor::visit(const fs::path &root) const
{
    std::unordered_multimap<EFileType, std::string> result;
    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(root, fs::directory_options::skip_permission_denied)) 
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
    }
    catch(const std::exception &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return {};
    }

    return result;
}
