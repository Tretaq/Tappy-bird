cmake_minimum_required(VERSION 3.22)
project(Tappy_bird)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.0)
FETCHCONTENT_MAKEAVAILABLE(SFML)


add_executable(Tappy_bird main.cpp
        Bird.h
        Bird.cpp
        Pipe.h
        Pipe.cpp
)

target_link_libraries(Tappy_bird PRIVATE SFML::Graphics SFML::Audio)