#ifndef MODEL_HPP
#define MODEL_HPP
#include "include.hpp"

class Model
{
private:
    unsigned int vaoId;
    unsigned int vertexCount;
    unsigned int textureId;

public:
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 position;

    Model();
    Model(const unsigned int, const unsigned int);
    unsigned int getVaoId();
    unsigned int getTextureId();
    void setTexture(const unsigned int);
    void setScale(glm::vec3);
    void setPosition(glm::vec3);
    void setRotation(glm::vec3);
    unsigned int getVertexCount();
};

#endif