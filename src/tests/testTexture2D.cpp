#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include <glm/gtx/string_cast.hpp>

#include "imgui/imgui.h"

#include "handleOpenGlErrors.h"


#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexArray.h"

#include "shader.h"

#include "renderer.h"

#include "tests/testClearColor.h"
#include "testTexture2D.h"

namespace test{
    TestTexture2D::TestTexture2D()
        :shader("res/shaders/Basic.shader"), translation(200.0f, 200.0f, 0.0f)
        ,texture ("res/textures/5_star.png")
    {
        float postions[16] = {
            100.0f, 100.0f,  0.0f, 0.0f,
            150.0f, 100.0f, 1.0f, 0.0f,
            150.0f, 150.0f, 1.0f, 1.0f,
            100.0f, 150.0f, 0.0f, 1.0f
        };

        proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GL_CALL(glEnable(GL_BLEND));


        vb = new VertexBuffer(postions, 4 * 4 * sizeof(float));


        VertexBufferLayout layout;
        layout.push({GL_FLOAT, 2, false});
        layout.push({GL_FLOAT, 2, false});

        va.AddBuffer(*vb, layout);

        ib = new IndexBuffer( indices, 6 );
        
       
        texture.bind();

        shader.setUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D()
    {
        free(ib);
        free(vb);
    }

    void TestTexture2D::onUpdate(float deltaTime)
    {
    }

    void TestTexture2D::onRender()
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        glm::mat4 MVP = proj * view * model;

        shader.bind();
        shader.setUniformMat4f("u_MVP", MVP);


        Renderer::Draw(va, *ib, shader);
    }   

    void TestTexture2D::onImGuiRender()
    {           
        ImGui::SliderFloat("Translation x", &translation.x, -960, 960);  
        ImGui::SliderFloat("Translation y", &translation.y, -540, 540);  
        ImGui::SliderFloat("Translation z", &translation.z, -1, 1);  
    }
}