#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "include.hpp"
#include "./model.hpp"

class Renderer
{
private:
    void prepareModel(Model);
    glm::vec3 backgroundColor;
    void unbindModel();

public:
    void clear();
    Renderer();
    void render(std::vector<Model>);
};

#endif