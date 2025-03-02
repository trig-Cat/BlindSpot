cmake_minimum_required(VERSION 3.17)

project(BlindSpot)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)
include_directories(external/**/include)
ADD_SUBDIRECTORY(src)




#[===[
file(GLOB SOURCES
    src/main.cpp
    src/hdr/LidarEngine/*.cpp
    src/hdr/LidarEngine/*.h
    src/hdr/LidarEngine/*.hpp
    src/hdr/*.cpp
    src/hdr/*.hpp
    src/hdr/*.h
)

add_executable(BlindSpot ${SOURCES})

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(FreeGLUT CONFIG REQUIRED)

target_link_libraries(BlindSpot PRIVATE glad::glad)

target_link_libraries(BlindSpot PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)

find_package(glm CONFIG REQUIRED)
target_link_libraries(BlindSpot PRIVATE glm::glm)


target_link_libraries(BlindSpot PRIVATE fmt::fmt)

target_link_libraries(BlindSpot PRIVATE glfw)
]===]
