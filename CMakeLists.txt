cmake_minimum_required(VERSION 3.24)
project(multimedia_finder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

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
)