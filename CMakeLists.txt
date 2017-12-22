cmake_minimum_required(VERSION 3.6)
project(hexagon-game-bot)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/main.cpp
        src/hexagon_bot.h
        src/hexagon_bot.cpp)
if (WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} src/tcp_server_win.cpp)
endif (WIN32)
if (UNIX)
    set(SOURCE_FILES ${SOURCE_FILES} src/tcp_server_linux.cpp)
endif (UNIX)
add_executable(hexagon-game-bot ${SOURCE_FILES})
