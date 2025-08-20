add_library(harmony-core
            note.cpp
            key.cpp
            interval.cpp
            clef.cpp
            bar.cpp
            list.cpp
            staff.cpp
            staff_system.cpp)

target_include_directories(harmony-core PUBLIC ${PROJECT_SOURCE_DIR}/include)
