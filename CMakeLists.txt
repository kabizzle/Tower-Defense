cmake_minimum_required(VERSION 3.11.0)

project(tower-defense)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB SRC_HPP "src/*.hpp")
file(GLOB SRC_CPP "src/*.cpp")
file(GLOB STATES_HPP "src/states/*.hpp")
file(GLOB STATES_CPP "src/states/*.cpp")
set(SOURCES ${SRC_HPP} ${SRC_CPP} ${STATES_HPP} ${STATES_CPP})

add_executable(tower-defense src/main.cpp)

target_sources(tower-defense PUBLIC ${SOURCES})
target_include_directories(tower-defense PUBLIC src)

find_package(SFML REQUIRED system window graphics audio)
target_link_libraries(tower-defense sfml-system sfml-window sfml-graphics sfml-audio)

if (MSVC)
    target_compile_options(tower_defense PRIVATE /Wall)
else()
    target_compile_options(tower-defense PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)
endif()
