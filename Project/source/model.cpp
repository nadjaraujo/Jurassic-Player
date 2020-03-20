#include "model.hpp"

Model::Model()
{
    vaoId = 0;
    vertexCount = 0;
}

Model::Model(const unsigned int p_vaoId, const unsigned int p_vertexCount)
{
    vaoId = p_vaoId;
    vertexCount = p_vertexCount;
}

unsigned int Model::getVaoId()
{
    return vaoId;
}

unsigned int Model::getVertexCount()
{
    return vertexCount;
}