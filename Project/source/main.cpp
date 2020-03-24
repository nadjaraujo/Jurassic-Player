#include "include.hpp"
#include "functions.hpp"
#include "renderer.hpp"
#include "model.hpp"
#include "loader.hpp"
#include <stdlib.h>
using namespace std;

//ESSAS SAO AS CORES QUE CORRESPONDEM AOS VERTICES
float timeValue;
float greenValue;
float redValue;
float blueValue;

int main()
{
    // função pra instanciar a janela do GLFW
    glfwInit();
    glwindowhint();

    //objeto janela
    GLFWwindow *window = glfwCreateWindow(800, 600, "janelinha da alegria", NULL, NULL);

    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // função glad para carregar a função do openGL

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /* -------------------------------------------
        CLOUD NE */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Shader ourShader("./source/texture.vs", "./source/texture.fs");

    Loader loader = Loader();
    std::vector<float> vertices = {-0.5f, 0.5f, -0.5f,
                                   -0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, -0.5f,
                                   0.5f, 0.5f, -0.5f,

                                   -0.5f, 0.5f, 0.5f,
                                   -0.5f, -0.5f, 0.5f,
                                   0.5f, -0.5f, 0.5f,
                                   0.5f, 0.5f, 0.5f,

                                   0.5f, 0.5f, -0.5f,
                                   0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, 0.5f,
                                   0.5f, 0.5f, 0.5f,

                                   -0.5f, 0.5f, -0.5f,
                                   -0.5f, -0.5f, -0.5f,
                                   -0.5f, -0.5f, 0.5f,
                                   -0.5f, 0.5f, 0.5f,

                                   -0.5f, 0.5f, 0.5f,
                                   -0.5f, 0.5f, -0.5f,
                                   0.5f, 0.5f, -0.5f,
                                   0.5f, 0.5f, 0.5f,

                                   -0.5f, -0.5f, 0.5f,
                                   -0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, 0.5f};

    std::vector<float> normalVec = {0.0f, 0.0f, -1.0f,
                                    0.0f, 0.0f, -1.0f,
                                    0.0f, 0.0f, -1.0f,
                                    0.0f, 0.0f, -1.0f,

                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,

                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,

                                    -1.0f, 0.0f, 0.0f,
                                    -1.0f, 0.0f, 0.0f,
                                    -1.0f, 0.0f, 0.0f,
                                    -1.0f, 0.0f, 0.0f,

                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,

                                    0.0f, -1.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f};

    std::vector<unsigned int> indices = {0, 1, 3,
                                         3, 1, 2,
                                         4, 5, 7,
                                         7, 5, 6,
                                         8, 9, 11,
                                         11, 9, 10,
                                         12, 13, 15,
                                         15, 13, 14,
                                         16, 17, 19,
                                         19, 17, 18,
                                         20, 21, 23,
                                         23, 21, 22};
    std::vector<float> textureCoords = {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0};

    int numeroArvores = 100;
    Renderer renderer = Renderer();
    unsigned int texture2 = loader.loadTexture("./Textura/tree.jpg");
    unsigned int texture1 = loader.loadTexture("./Textura/dinoskin.jpg");

    std::vector<Model> modelos;
    for (int i = 0; i < numeroArvores; i++)
    {
        Model modelo = loader.loadObj("./Modelos/tree.obj");
        modelo.setPosition(glm::vec3(1.0f + (rand() % 100 - 50), -5.0f, 0.0f + (rand() % 100 - 50)));

        modelo.setTexture(texture2);
        // int texture1 = loader.loadTexture("./Textura/checkerboard.png");

        modelos.push_back(modelo);
    }

    Model modelo1 = loader.loadObj("./Modelos/trex.obj");
    modelo1.setPosition(glm::vec3(-5.0f, 0.0, -5.0));
    //modelo1.setScale(glm::vec3(50.0, 0.0, 0.0));
    modelo1.setTexture(texture1);
    modelos.push_back(modelo1);

    unsigned int textureChao = loader.loadTexture("./Textura/grass2.jpg");
    Model chao = loader.loadVAO(vertices, indices, textureCoords, normalVec); // o chão hehe
    chao.setTexture(textureChao);
    chao.setPosition(glm::vec3(0.0f, -6.0f, 0.0f));
    chao.setScale(glm::vec3(500.0f, 0.5f, 500.0f));

    modelos.push_back(chao);

    unsigned int textureSol = loader.loadTexture("./Textura/2k_sun.jpg");
    Model Sol = loader.loadVAO(vertices, indices, textureCoords, normalVec);
    Sol.setTexture(textureSol);
    glm::vec3 lightPos(.0f, 20.0f, .0f);
    Sol.setPosition(lightPos);
//    Sol.setScale(glm::vec3(500.0f, 0.5f, 500.0f));
    modelos.push_back(Sol);
    //ourShader.use();

    // loop de renderização

    Camera camera;
    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();
        camera.processInput(window);
        camera.handleMouse(window);

        //ourShader.use();

        //unsigned int shaderProgram = glGetUniformLocation(ourShader.ID, "transform");
        //glUniformMatrix4fv(shaderProgram, 1, GL_FALSE, glm::value_ptr(transform));
        renderer.render(camera, modelos);

        // // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer.cleanUp();

    //limpar memoria
    glfwTerminate();
    return 0;
}
