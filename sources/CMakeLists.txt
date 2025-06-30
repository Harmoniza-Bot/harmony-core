add_library(harmony-core
            note.cpp
            accidental.cpp
            octave.cpp
            key.cpp)

target_include_directories(harmony-core PUBLIC ${PROJECT_SOURCE_DIR}/include)
