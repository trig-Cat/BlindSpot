cmake_minimum_required(VERSION 3.10)

project(BlindSpot)

add_executable(BlindSpot main.cpp)

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(BlindSpot PRIVATE fmt::fmt)

target_link_libraries(BlindSpot PRIVATE glfw)
target_link_libraries(BlindSpot PRIVATE glad)