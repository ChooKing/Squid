cmake_minimum_required(VERSION 4.1)
project(Squid)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG a962f40bbba175e9716557a25d5d7965f134a3d3
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL)

add_library(Squid src/Squid.cpp
        include/Squid.h
        src/AppWindow.cpp
        src/AppWindow.h)

add_executable(Example example/main.cpp)

target_include_directories(Squid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Squid PUBLIC SDL3::SDL3-static)
target_link_libraries(Example PRIVATE Squid)
