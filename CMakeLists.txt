cmake_minimum_required(VERSION 3.22)
project(Tappy_bird)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

FETCHCONTENT_DECLARE(SFML
        URL https://github.com/SFML/SFML/archive/refs/tags/3.0.0.zip
)
fetchcontent_makeavailable(SFML)

add_executable(Tappy_bird main.cpp)

target_link_libraries(Tappy_bird PRIVATE SFML::Graphics)