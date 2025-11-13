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

# Используем модуль поиска CImg
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")

# Подключаем CImg
find_package(CImg REQUIRED)

# Включаем интерфейсы CImg
target_link_libraries(harmony-core PUBLIC CImg::CImg)

