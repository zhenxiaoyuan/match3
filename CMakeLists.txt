cmake_minimum_required(VERSION 3.20.0)
project(match3 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(match3 src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

find_library(LIB_SDL_D NAMES SDL3d PATHS lib REQUIRED)
find_library(LIB_SDL_MAIN_D NAMES  SDL3_maind PATHS lib REQUIRED)

target_link_libraries(${PROJECT_NAME} ${LIB_SDL_D} ${LIB_SDL_MAIN_D})
