#include "scene.h"

int main(int argc, char **argv) {
    Scene::width = 600;
    Scene::heigth = 600;

    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(Scene::width, Scene::heigth, "ray", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    Scene::setup();

//    glutDisplayFunc(Scene::render(win));
//    glutMainLoop();

    // Set the required callback functions
//    glfwSetKeyCallback(window, Scene::render);

    // loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        Scene::render();

        glfwSwapBuffers(window);
    }

    return 0;
}
