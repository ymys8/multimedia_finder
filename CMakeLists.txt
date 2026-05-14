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

target_sources(multimedia_finder PRIVATE 
    checkmanager.h
    checker.h
    dirvisitor.h
    reportwriter.h

    checkmanager.cpp
    checker.cpp
    dirvisitor.cpp
    reportwriter.cpp
    main.cpp

    utils.hpp
)

target_link_libraries(multimedia_finder PRIVATE
    nlohmann_json::nlohmann_json
)