#pragma once

#include "checker.h"

#include <filesystem>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace fs = std::filesystem;

namespace httplib
{
class Server;
}

/// Перечисление для видов отчета поиска
enum class EReportType : uint8_t
{
    JSON = 0, ///< В виде файла json
    HTTP      ///< Через http по адресу http://localhost:1234/media_files
};

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
};

/// Класс для записи отчета через http
class HTTPWriter : public IReportWriter
{
public:
    /// Конструктор. Сразу поднимает HTTP-сервер на localhost:port
    explicit HTTPWriter(const std::string &host = "localhost", int port = 1234);
    /// Деструктор
    ~HTTPWriter() override;

    HTTPWriter(const HTTPWriter &) = delete;
    HTTPWriter &operator=(const HTTPWriter &) = delete;
    HTTPWriter(HTTPWriter &&) = delete;
    HTTPWriter &operator=(HTTPWriter &&) = delete;

    /// Обновить хранимый JSON-отчет
    void writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const override;

private:
    std::unique_ptr<httplib::Server> _server; ///< HTTP-сервер
    std::thread _serverThread;                ///< Поток, в котором крутится listen()

    mutable std::mutex _mutex;                                                       ///< Защищает _currentReport
    mutable std::string _currentReport{"{\"audio\":[],\"video\":[],\"images\":[]}"}; ///< Текущий JSON-отчет
};
