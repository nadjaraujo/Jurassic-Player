#include "renderer.hpp"

Renderer::Renderer() : backgroundColor(0, 0, 0) {}

void Renderer::render(std::vector<Model> models)
{

    for (Model &model : models)
    {

        prepareModel(model);

        glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindModel();
    }
}

void Renderer::prepareModel(Model model)
{

    // Bind VAO and VBOS ( Position, Texture)
    glBindVertexArray(model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Renderer::unbindModel()
{

    // Disable VBOs
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    // Unbind VAO
    glBindVertexArray(0);
}

void Renderer::clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1);

    glEnable(GL_DEPTH_TEST);
}
