cmake_minimum_required(VERSION 3.10)

project(BlindSpot)

file(GLOB SOURCES
    src/main.cpp
        hdr/LidarEngine/*.cpp
        hdr/LidarEngine/*.h
        hdr/LidarEngine/*.hpp
        hdr/*.cpp
        hdr/*.hpp
        hdr/*.h
)

add_executable(BlindSpot ${SOURCES})

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(FreeGLUT CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(BlindSpot PRIVATE glad::glad)

target_link_libraries(BlindSpot PRIVATE glm::glm)
target_link_libraries(BlindSpot PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)


target_link_libraries(BlindSpot PRIVATE fmt::fmt)

target_link_libraries(BlindSpot PRIVATE glfw)
