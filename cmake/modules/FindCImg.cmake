# FindCImg.cmake
# Найти расположение CImg.h

if(NOT CImg_FOUND)
    # Стандартные места поиска
    find_path(CImg_INCLUDE_DIR NAMES CImg PATHS
              "$ENV{CIMG_ROOT}"
              "${CMAKE_INSTALL_PREFIX}/include"
              "/usr/include"
              "/usr/local/include"
              NO_DEFAULT_PATH
    )

    if(CImg_INCLUDE_DIR)
        message(STATUS "Found CImg headers: ${CImg_INCLUDE_DIR}")
        set(CImg_FOUND TRUE CACHE INTERNAL "")
    else()
        message(FATAL_ERROR "Could NOT find CImg header.")
    endif()
endif()

mark_as_advanced(
    CImg_INCLUDE_DIR
)

# Интерфейсы для дальнейшего использования
if(CImg_FOUND AND NOT TARGET CImg::CImg)
    add_library(CImg::CImg INTERFACE IMPORTED GLOBAL)
    target_include_directories(CImg::CImg SYSTEM INTERFACE ${CImg_INCLUDE_DIR})
endif()
