#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "LIDAR/LidarEngine.h"

using namespace std;

LidarEngine* lidarEngine;

int main(int argc, char const *argv[])
{
    glfwInit();

    lidarEngine->initializeGL();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "yooo", nullptr, nullptr);
    // ERROR CHECK
    if (window == nullptr) {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 600);


    glClearColor(0.56f, 0.3f, 0.31f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// LidarEngine* enginePtr = nullptr;
// bool useBurstMode = false;

// void displayCallback() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     enginePtr->fireRays(useBurstMode);
//     glutSwapBuffers();
// }

// void reshapeCallback(int w, int h) {
//     glViewport(0, 0, w, h);
// }

// void keyboardCallback(unsigned char key, int x, int y) {
//     if(key == 'b' || key == 'B') {
//         useBurstMode = !useBurstMode;
//     }
//     glutPostRedisplay();
// }

// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitContextVersion(3, 3);
//     glutInitContextProfile(GLUT_CORE_PROFILE);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("Lidar Engine");
    
//     if (!gladLoadGL()) {
//         return -1;
//     }
    
//     glEnable(GL_DEPTH_TEST);
//     enginePtr = new LidarEngine(5000);
//     enginePtr->setCameraPosition(glm::vec3(0.0f, 0.0f, 0.0f));
//     enginePtr->addObject(WorldObject(glm::vec3(0.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 1.0f), false));
//     enginePtr->addObject(WorldObject(glm::vec3(2.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), true));
    
//     glutDisplayFunc(displayCallback);
//     glutReshapeFunc(reshapeCallback);
//     glutKeyboardFunc(keyboardCallback);
//     glutMainLoop();
    
//     delete enginePtr;
//     return 0;
// }