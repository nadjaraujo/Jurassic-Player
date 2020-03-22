#include "model.hpp"

Model::Model()
{
    vaoId = 0;
    vertexCount = 0;
    textureId = 0;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Model::Model(const unsigned int p_vaoId, const unsigned int p_vertexCount)
{
    vaoId = p_vaoId;
    vertexCount = p_vertexCount;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Model::setPosition(glm::vec3 p_position)
{
    position = p_position;
}

unsigned int Model::getTextureId()
{
    return textureId;
}

void Model::setRotation(glm::vec3 p_rotation)
{
    rotation = p_rotation;
}

void Model::setScale(glm::vec3 p_scale)
{
    scale = p_scale;
}

void Model::setTexture(unsigned int p_textureId)
{
    textureId = p_textureId;
}

unsigned int Model::getVaoId()
{
    return vaoId;
}

unsigned int Model::getVertexCount()
{
    return vertexCount;
}
