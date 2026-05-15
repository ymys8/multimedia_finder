#pragma once

#include <filesystem>

namespace fs = std::filesystem;

/// Тип медиафайла
enum class EFileType : uint8_t
{
    None = 0, ///< Не медиафайл
    Audio,    ///< Аудио
    Video,    ///< Видео
    Image     ///< Картинка
};

/// Интерфейс для проверки файла по признакам
class IFileChecker
{
  public:
    /// Конструктор
    IFileChecker() = default;
    /// Деструктор
    virtual ~IFileChecker() = default;

    /// Получить тип файла при проверке
    virtual EFileType check(const fs::path &file) const = 0;
};

/// Класс для проверки медиафайлов
class MultimediaChecker : public IFileChecker
{
  public:
    /// Конструктор
    MultimediaChecker() = default;
    /// Деструктор
    ~MultimediaChecker() = default;

    /// Проверить медиафайл
    virtual EFileType check(const fs::path &file) const override;
};