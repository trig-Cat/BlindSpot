#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    glfwInit();

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
