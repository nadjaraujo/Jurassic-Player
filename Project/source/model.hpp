#ifndef MODEL_HPP
#define MODEL_HPP
#define

class Model
{
private:
    unsigned int vaoId;
    unsigned int vertexCount;
    unsigned int textureId;

public:
    Model();
    Model(const unsigned int, const unsigned int);
    unsigned int getVaoId();
    unsigned int getVertexCount();
};

#endif