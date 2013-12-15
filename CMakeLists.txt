cmake_minimum_required(VERSION 2.6)

project(gammapersei)

file(
    GLOB_RECURSE
    src
    src/*
)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(
    gammapersei
    ${src}
)

target_link_libraries(
    gammapersei
    SDL
    SDL_image
    SDL_ttf
    SDL_mixer
    luajit-5.1
    GL
    GLU
)


