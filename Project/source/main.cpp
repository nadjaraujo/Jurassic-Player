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

//VERTICES UTILIZADOS
std::vector<float> vertices = {
    // positions         // colors
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

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

    Shader ourShader("./source/texture.vs", "./source/texture.fs");

    Loader loader = Loader();
    std::vector<float> positions = {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
    std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};
    std::vector<float> textureCoords = {1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

    Model modelo = Model(loader.loadVAO(vertices, indices));

    Renderer renderer = Renderer();

    unsigned int texture1 = loader.loadTexture("./Textura/container.jpg");
    unsigned int texture2 = loader.loadTexture("./Textura/Ednaldo_Pereira.jpg");

    std::vector<Model> modelos;

    modelos.push_back(modelo);

    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);


	//ADICIONANDO PROFUNDIDADE (PERSPECTIVA)
	glm::mat4 model = glm::mat4(1.0f); // Tem as translações, escalas e/ou rotações que queremos aplicar nos objetos do world space
	glm::mat4 view = glm::mat4(1.0f); // Tem a matriz view, ela move a cena inteira
	glm::mat4 projection; // Matriz de projeção

	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //rotacionando o eixo x
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); //movendo a cena um pouco pra trás no eixo z para poder enxergar a transformação - ele inicialmente fica no eixo 0,0,0
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // "deitando" a imagem em 45 rad

	//alocando as informações
	int modelLoc = glGetUniformLocation(ourShader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	int viewLoc = glGetUniformLocation(ourShader.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
	ourShader.setMat4("projection", projection);


    // loop de renderização
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
     	renderer.clear();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //transform = glm::scale(transform, glm::vec3(1.0f, 2.0f, 1.0f));

        ourShader.use();

        //unsigned int shaderProgram = glGetUniformLocation(ourShader.ID, "transform");
        //glUniformMatrix4fv(shaderProgram, 1, GL_FALSE, glm::value_ptr(transform));
        renderer.render(modelos);


        // // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //limpar memoria
    glfwTerminate();
    return 0;
}
