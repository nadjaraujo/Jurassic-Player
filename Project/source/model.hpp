#ifndef MODEL_HPP
#define MODEL_HPP

class Model
{
private:
    unsigned int vaoId;
    unsigned int vertexCount;

public:
    Model();
    Model(const unsigned int, const unsigned int);
    unsigned int getVaoId();
    unsigned int getVertexCount();
};

#endif