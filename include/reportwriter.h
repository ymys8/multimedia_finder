#pragma once

#include "checker.h"

#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

/// Интерфейс для записи отчета
class IReportWriter
{
public:
    /// Конструктор
    IReportWriter() = default;
    /// Деструктор
    virtual ~IReportWriter() = default;

    /// Записать отчет
    virtual void writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const = 0;
};

/// Класс для записи отчета в формате JSON
class JSONWriter : public IReportWriter
{
public:
    /// Конструктор
    JSONWriter() = default;
    /// Деструктор
    virtual ~JSONWriter() = default;

    /// Записать отчет
    virtual void writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const override;

private:
    /// Перевести тип медиафайла в строку
    std::string fileType2Str(EFileType type) const;
};