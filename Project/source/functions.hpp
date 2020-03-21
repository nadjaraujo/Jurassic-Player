
#include <GLFW/glfw3.h>
#include <iostream>

//----------------------------------------------------------------------------------------
//FUNCOES REFERENTES A JANELAS
//redimenciona a janela para a viewport
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//entrada de controle
void processInput(GLFWwindow *window)
{
    // função que recebe janela e tecla "esc" como entrada
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void glwindowhint()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

