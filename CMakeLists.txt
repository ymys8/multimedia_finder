cmake_minimum_required(VERSION 3.16)
project(multimedia_finder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
 
include(FetchContent)
 
# JSON-библиотека
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# Чтобы не добавлять лишних зависимостей
set(HTTPLIB_USE_OPENSSL_IF_AVAILABLE OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_ZLIB_IF_AVAILABLE    OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_BROTLI_IF_AVAILABLE  OFF CACHE BOOL "" FORCE)
set(HTTPLIB_USE_ZSTD_IF_AVAILABLE    OFF CACHE BOOL "" FORCE)
 
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG        v0.41.0
)
FetchContent_MakeAvailable(httplib)
 
add_executable(multimedia_finder)
 
target_include_directories(multimedia_finder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
 
target_sources(multimedia_finder PRIVATE
    src/checkmanager.cpp
    src/checker.cpp
    src/dirvisitor.cpp
    src/reportwriter.cpp
    src/main.cpp
)
 
target_link_libraries(multimedia_finder PRIVATE
    nlohmann_json::nlohmann_json
    httplib::httplib
    Threads::Threads
)
