#pragma once

#include <cstdint>
#include <filesystem>

#include "dirvisitor.h"
#include "reportwriter.h"

namespace fs = std::filesystem;

/// Класс-оркестратор для выполнения основных шагов при поиске
class CheckManager
{
public:
    /// Конструктор
    /// @param repeatingTime время между запусками в секундах
    explicit CheckManager(size_t repeatingTime, const fs::path &checkingDir, EReportType reportType);
    /// Деструктор
    ~CheckManager() = default;

    /// Запустить поиск медиафайлов
    void run() const;

private:
    /// Инициализировать класс для записи отчета
    void initWriter(EReportType reportType);

    const size_t _repeatingTime; ///< Время между обходами
    fs::path _checkingDir;       ///< Путь до директории, откуда начинается проверка

    std::unique_ptr<DirVisitor> visitor;   ///< Рекурсивный обходчик по директории
    std::unique_ptr<IReportWriter> writer; ///< Класс для записи отчета проверки
};