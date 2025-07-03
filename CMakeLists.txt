cmake_minimum_required(VERSION 3.15)

project(harmony-core
        VERSION 0.1.0
        DESCRIPTION "Позволяет работать с музыкальными нотациями."
        HOMEPAGE_URL "https://github.com/harmoniza-bot/harmony-core"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

target_include_directories(harmony-core PUBLIC ${PROJECT_SOURCE_DIR}/sources/include)

add_subdirectory(sources)
