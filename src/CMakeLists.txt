file(GLOB SOURCES
    main.cpp
    hdr/LidarEngine/*.cpp
    hdr/LidarEngine/*.h
    hdr/LidarEngine/*.hpp
    hdr/*.cpp
    hdr/*.hpp
    hdr/*.h
)

add_executable(BSrc ${SOURCES})

find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(FreeGLUT CONFIG REQUIRED)

target_link_libraries(BSrc PRIVATE glad::glad)

target_link_libraries(BSrc PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)

find_package(glm CONFIG REQUIRED)
target_link_libraries(BSrc PRIVATE glm::glm)


target_link_libraries(BSrc PRIVATE fmt::fmt)

target_link_libraries(BSrc PRIVATE glfw)

find_package(GLUT REQUIRED)
target_link_libraries(BSrc PRIVATE GLUT::GLUT)