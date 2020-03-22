#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "include.hpp"
#include <GLFW/glfw3.h>
class Camera
{

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    bool firstMouse;
    float lastX;
    float lastY;

    float pitch;
    float yaw;
    float roll;

public:
    Camera();
    void move(GLFWwindow *window);

    glm::vec3 getPosition();
    float getPitch();
    float getYaw();
    glm::vec3 getFront();
    glm::vec3 getUp();
    void processInput(GLFWwindow *window);
    void handleMouse(GLFWwindow *window);
};

#endif // CAMERA_HPP