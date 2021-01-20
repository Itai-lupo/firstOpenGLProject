#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "renderer.h"

#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexArray.h"

#include "shader.h"

#include "texture.h"

using namespace std;



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        std::cout << "error" <<endl;

    float postions[16] = {
        100.0f, 100.0f,  0.0f, 0.0f,
        150.0f, 100.0f, 1.0f, 0.0f,
        150.0f, 150.0f, 1.0f, 1.0f,
        100.0f, 150.0f, 0.0f, 1.0f
    };

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);



    unsigned int indices[6] = {
         0, 1, 2,
         2, 3, 0
     };

    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_CALL(glEnable(GL_BLEND));

    VertexArray va;

    VertexBuffer *vb = new VertexBuffer(postions, 4 * 4 * sizeof(float));


    VertexBufferLayout layout;
    layout.push({GL_FLOAT, 2, false});
    layout.push({GL_FLOAT, 2, false});

    va.AddBuffer(*vb, layout);

    IndexBuffer *ib = new IndexBuffer( indices, 6 );



    Shader shader("res/shaders/Basic.shader");
    
    shader.bind();
    shader.setUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
    shader.setUniformMat4f("u_MVP", proj);

    Texture texture("res/textures/5_star.png");
    texture.bind();

    shader.setUniform1i("u_Texture", 0);

    Renderer renderer;
    /* Loop until the user closes the window */
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        i = (i + 50) % 1000;
        shader.setUniform4f("u_Color", ((float)((i + 300)%1000))/1000, ((float)((i + 600)%1000))/1000, ((float)((i + 900)%1000))/1000, 1.0f);
        
        /* Render here */
        renderer.Clear();        
        renderer.Draw(va, *ib, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    free(vb);
    free(ib);

    cout << "end" << endl;
    return 0;
}