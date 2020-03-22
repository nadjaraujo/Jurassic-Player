#include "include.hpp"
#include "functions.hpp"
#include "renderer.hpp"
#include "model.hpp"
#include "loader.hpp"

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

    Model modelo = loader.loadVAO(vertices, indices, textureCoords);
    modelo.setPosition(glm::vec3(0.0f, 0.0f, -2.0f));
    Renderer renderer = Renderer();

    // int texture1 = loader.loadTexture("./Textura/checkerboard.png");

    unsigned int texture2 = loader.loadTexture("./Textura/Ednaldo_Pereira.jpg");
    modelo.setTexture(texture2);
    std::vector<Model> modelos;

    modelos.push_back(modelo);

    //ourShader.use();

    // loop de renderização

    Camera camera;
    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();
        camera.processInput(window);
        //camera.handleMouse(window);

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
