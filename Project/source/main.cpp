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
std::vector<float> vertices= {
    // positions         // colors
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
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

	Shader ourShader("texture.vs", "texture.fs");

    Loader loader = Loader();
    std::vector<float> positions = {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f};
    std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};
    std::vector<float> textureCoords = {1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	Model modelo = Model(loader.loadVAO(vertices, indices));

	Renderer renderer = Renderer();

	unsigned int texture1 = loader.loadTexture("../Textura/container.jpg");
	unsigned int texture2 = loader.loadTexture("../Textura/Ednaldo_Pereira.jpg");

	std::vector<Model> modelos;


    modelos.push_back(modelo);

	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);



	// loop de renderização
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);


		//Seta a cor do fundo e limpa o buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		ourShader.use();

		unsigned int shaderProgram = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(shaderProgram, 1, GL_FALSE, glm::value_ptr(transform));
		renderer.render(modelos);




		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // limpar o buffer com essa cor :)
        // glClear(GL_COLOR_BUFFER_BIT);
        // timeValue = glfwGetTime();
        // greenValue = sin(timeValue);
        // redValue = cos(timeValue);
        // blueValue = (redValue + greenValue) / 2.0f;
        // if (greenValue < 0)
        //     greenValue = greenValue * -1;
        // if (redValue < 0)
        //     redValue = redValue * -1;
        // if (blueValue < 0)
        //     blueValue = blueValue * -1;
        // vertices[3] = greenValue;
        // vertices[10] = redValue;
        // vertices[17] = blueValue;
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); //carregando vertices no buffer

        // //    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // //    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        // // draw our first triangle

        // glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        // glDrawArrays(GL_TRIANGLES, 0, 3); //desenhando

        // // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    //limpar memoria
    glfwTerminate();
    return 0;
}
