file(GLOB SOURCES
  *.cpp
  *.hpp
  *.h
  **/*.cpp
  **/*.hpp
  **/*.h
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

find_package(OpenGL REQUIRED)
target_link_libraries(BlindSpot PRIVATE OpenGL::GL)
target_link_libraries(BlindSpot PRIVATE fmt::fmt)

target_link_libraries(BlindSpot PRIVATE glfw)