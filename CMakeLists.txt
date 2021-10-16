cmake_minimum_required(VERSION 3.20)
project(2048)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lncurses")
if (LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ltinfo")
endif ()
add_executable(2048 main.cpp src/engine/engine.cpp src/game.cpp src/ui/text_ui.cpp)
