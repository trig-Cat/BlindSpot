file(GLOB SOURCES
  *.cpp
  *.hpp
  *.h
  **/*.cpp
  **/*.hpp
  **/*.h
)

add_executable(BlindSpot ${SOURCES})
target_include_directories(BlindSpot PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(BlindSpot PRIVATE ${CMAKE_SOURCE_DIR}/external/**/include)
target_link_libraries(BlindSpot PRIVATE SDL3::SDL3)
target_link_libraries(BlindSpot PRIVATE glm::glm)
