#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));


    unsigned int indices[6] = {
         0, 1, 2,
         2, 3, 0
     };

    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_CALL(glEnable(GL_BLEND));

    VertexArray va;

    VertexBuffer *vb = new VertexBuffer(postions, 16 * sizeof(float));


    VertexBufferLayout layout;
    layout.push({GL_FLOAT, 2, false});
    layout.push({GL_FLOAT, 2, false});

    va.AddBuffer(*vb, layout);

    IndexBuffer *ib = new IndexBuffer( indices, 6 );



    Shader shader("res/shaders/Basic.shader");
    
    shader.bind();
    shader.setUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

    Texture texture("res/textures/5_star.png");
    texture.bind();

    shader.setUniform1i("u_Texture", 0);

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui::StyleColorsDark();
    
    glm::vec3 translation(200.0f, 200.0f, 0.0f);
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        glm::mat4 MVP = proj * view * model;

        i = (i + 50) % 1000;
        shader.setUniform4f("u_Color", ((float)((i + 300)%1000))/1000, ((float)((i + 600)%1000))/1000, ((float)((i + 900)%1000))/1000, 1.0f);
        shader.setUniformMat4f("u_MVP", MVP);
        

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Render here */
        renderer.Clear();        
        renderer.Draw(va, *ib, shader);


        {
            
            ImGui::SliderFloat("Translation x", &translation.x, -960, 960);  
            ImGui::SliderFloat("Translation y", &translation.y, -540, 540);  
            ImGui::SliderFloat("Translation z", &translation.z, -1, 1);  

            // ImGui::SliderFloat("z", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
          
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            // ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    free(vb);
    free(ib);

    cout << "end" << endl;
    return 0;
}