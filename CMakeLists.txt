cmake_minimum_required(VERSION 3.15)

project(harmony-core
        VERSION 0.1.0
        DESCRIPTION "Позволяет работать с музыкальными нотациями."
        HOMEPAGE_URL "https://github.com/harmoniza-bot/harmony-core"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(sources)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

target_link_libraries(harmony-core PRIVATE ${X11_LIBRARIES})
target_include_directories(harmony-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CImg)
