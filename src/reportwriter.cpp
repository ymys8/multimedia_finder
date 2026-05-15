#include "reportwriter.h"
#include "utils.hpp"

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace nlohmann;

void JSONWriter::writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const
{
    json result = {{"audio", json::array()}, {"video", json::array()}, {"images", json::array()}};

    for (const auto &[type, path] : rawInfo)
    {
        result[Utils::fileType2Str(type)].push_back(path);
    }

    std::string savingPath = Utils::getHomeDir().string() + "/.media_files";
    std::ofstream file(savingPath);
    if (!file.is_open())
    {
        throw std::runtime_error("Не удалось открыть файл на запись");
    }
    file << result.dump(2);
}

HTTPWriter::HTTPWriter(const std::string &host, int port)
    : _server(std::make_unique<httplib::Server>())
{
    _server->Get("/media_files", [this](const httplib::Request &, httplib::Response &res) {
        std::string snapshot;
        {
            std::lock_guard<std::mutex> lock(_mutex);
            snapshot = _currentReport;
        }
        res.set_content(snapshot, "application/json");
    });

    _serverThread = std::thread([this, host, port]() {
        if (!_server->listen(host, port))
        {
            std::cerr << "HTTPWriter: не удалось запустить сервер на "
                      << host << ":" << port << std::endl;
        }
    });
 
    _server->wait_until_ready();
    if (!_server->is_running())
    {
        if (_serverThread.joinable())
        {
            _serverThread.join();
        }
        throw std::runtime_error("HTTPWriter: сервер не смог запуститься (порт " +
                                 std::to_string(port) + " занят?)");
    }
 
    std::cout << "HTTP-сервер запущен на http://" << host << ":" << port
              << "/media_files" << std::endl;
}
 
HTTPWriter::~HTTPWriter()
{
    if (_server)
    {
        _server->stop();
    }

    if (_serverThread.joinable())
    {
        _serverThread.join();
    }
}
 
void HTTPWriter::writeReport(const std::unordered_multimap<EFileType, std::string> &rawInfo) const
{
    json result = {{"audio", json::array()}, {"video", json::array()}, {"images", json::array()}};
    for (const auto &[type, path] : rawInfo)
    {
        result[Utils::fileType2Str(type)].push_back(path);
    }
    std::string serialized = result.dump(2);

    {
        std::lock_guard<std::mutex> lock(_mutex);
        _currentReport = std::move(serialized);
    }
}
