#include "loader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp" //biblioteca para as texturas

Model Loader::loadVAO(const std::vector<float> &position, const std::vector<unsigned int> &indices, const std::vector<float> &textureCoords)
{
    // Create VAO
    unsigned int vaoId = createVAO();
    bindIndicesBuffer(indices);
    // Store model positionitions on VAO 0
    storeDataInAttributeList(0, 3, position);
    //storeDataInAttributeList(1, 2, textureCoords);
    //storeDataInAttributeList(2, 2, position);
    storeDataInAttributeList(1, 2, textureCoords);

    // Unbind
    unbindVAO();
    // Return RawModel

    return Model(vaoId, indices.size());
}

unsigned int Loader::createVAO()
{

    unsigned int vaoId;
    // Create one Vertex Array (VAO) and keep address
    glGenVertexArrays(1, &vaoId);
    // Add VAO to vector
    vaos.push_back(vaoId);
    // Bind VAO
    glBindVertexArray(vaoId);
    return vaoId;
}

void Loader::storeDataInAttributeList(const unsigned int attributeNumber, const unsigned int size, const std::vector<float> &data)
{
    unsigned int vboID;
    // Generate buffer object of size 1 and store it in vboID
    glGenBuffers(1, &vboID);
    // Add VBO to vector
    vbos.push_back(vboID);
    // Bind the Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, false, 0, 0);
    // Unbind Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    // Unbind the Vertex Array
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> indices)
{

    unsigned int vboID;
    // Generate buffer object of size 1 and store it in vboID
    glGenBuffers(1, &vboID);
    // Add VBO to vector
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.at(0)), indices.data(), GL_STATIC_DRAW);
}

// função para carregar texturas "container.jpg"
unsigned int Loader::loadTexture(const std::string fileName)
{
    unsigned int textureId;
    int width, height, nrChannels;

    glGenTextures(1, &textureId);            //recebe qtd de texturas como entrada e armazena em texture;
    glBindTexture(GL_TEXTURE_2D, textureId); //gera textura

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(false);

    unsigned char *image = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);

    return textureId;
}
