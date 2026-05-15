#pragma once

#include "checker.h"

#include <unordered_map>

namespace fs = std::filesystem;

/// Класс для рекурсивного обхода директории
class DirVisitor
{
public:
    /// Конструктор
    DirVisitor();
    /// Деструктор
    ~DirVisitor() = default;

    /// Посетить диреткторию и вернуть список медиафайлов
    std::unordered_multimap<EFileType, std::string> visit(const fs::path &root) const;

private:
    std::unique_ptr<IFileChecker> checker; ///< Класс проверки файлов по необходимым признакам 
};