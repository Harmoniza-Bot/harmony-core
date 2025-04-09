cmake_minimum_required(VERSION 3.15)
project(harmony-core
        VERSION 0.1.0
        DESCRIPTION "Позволяет работать с музыкальными нотациями."
        HOMEPAGE_URL "https://github.com/harmoniza-bot/harmony-core"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(sources)
