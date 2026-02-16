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

FetchContent_Declare(freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG 3bd82b5f543bc84ccf2b1d0cdb63b95218099ee6
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)

set(freetype_shared OFF CACHE BOOL "" FORCE)
set(freetype_static ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(freetype)

add_library(Squid src/Squid.cpp
        include/Squid.h
        src/AppWindow.cpp
        src/AppWindow.h
        src/typography/Font.cpp
        src/typography/Font.h
        src/typography/Text.cpp
        src/typography/Text.h
        src/Buffer.cpp
        src/Buffer.h
        src/globals.h)

add_executable(Example example/main.cpp)

target_include_directories(Squid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Squid PUBLIC SDL3::SDL3-static freetype)
target_link_libraries(Example PRIVATE Squid)

add_custom_command(TARGET Squid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Squid>/assets
        COMMENT "Copying assets to output directory"
)