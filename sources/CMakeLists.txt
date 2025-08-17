add_library(harmony-core
            note.cpp
            key.cpp
            interval.cpp
            clef.cpp
            list.cpp
            staff.cpp
            staff_system.cpp)

target_include_directories(harmony-core PUBLIC ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(hc2img PUBLIC ${PROJECT_SOURCE_DIR}/include)
