#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"
class Renderer
{
private:
    void prepareModel(Model);
    glm::vec3 backgroundColor;
    void unbindModel();

    constexpr static GLfloat FOV = 45.0f;
    constexpr static GLfloat NEAR_PLANE = 0.1f;
    constexpr static GLfloat FAR_PLANE = 100.0f;

    glm::mat4 projectionMatrix;
    void createProjectionMatrix();

public:
    Shader shader;
    void clear();
    Renderer();
    void render(Camera t_camera, std::vector<Model>);
    void cleanUp();
};

#endif