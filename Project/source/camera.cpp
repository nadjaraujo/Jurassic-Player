#include "camera.hpp"

Camera::Camera()
{

    position = glm::vec3(0, 0, 2.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    firstMouse = true;
    lastX = 800.0f / 2.0;
    lastY = 600.0 / 2.0;
    yaw = 0;
    roll = 0;
    pitch = 0;
}

void Camera::handleMouse(GLFWwindow *window)
{

    GLdouble xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}

void Camera::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 0.1f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += cameraSpeed * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= cameraSpeed * front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
    //     if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    //         yaw -= cameraSpeed * 15;
    //     if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    //         yaw += cameraSpeed * 15;

    //     front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    //     front.y = sin(glm::radians(pitch));
    //     front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //     front = glm::normalize(front);
}

void Camera::move(GLFWwindow *window)
{
    const float cameraSpeed = 0.1f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position.z -= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position.z += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position.x -= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position.x += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        yaw -= cameraSpeed * 15;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        yaw += cameraSpeed * 15;
}

float Camera::getPitch()
{

    return this->pitch;
}

float Camera::getYaw()
{

    return this->yaw;
}

glm::vec3 Camera::getPosition()
{

    return this->position;
}

glm::vec3 Camera::getFront()
{
    return this->front;
}

glm::vec3 Camera::getUp()
{
    return this->up;
}