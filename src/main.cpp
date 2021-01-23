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

#include "tests/test.h"
#include "tests/testClearColor.h"
#include "tests/testClearColor2.h"

#include "tests/testMenu.h"

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

    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_CALL(glEnable(GL_BLEND));

    Renderer renderer;

    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
    

    test::Test *test = new test::TestClearColor();

    test::testMenu menu(&test);

    menu.registerTest<test::TestClearColor>("clear color test");
    menu.registerTest<test::TestClearColor2>("clear color test2");

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        renderer.Clear(); 
        if(menu.isTestEnabeld()){
            test->onUpdate(0.0f);
            test->onRender();
        }

        ImGui::NewFrame();
        if(menu.isTestEnabeld())
            test->onImGuiRender();
            
        menu.onImGuiRender();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    if(menu.isTestEnabeld())
        free(test);
    free(menu);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    cout << "end" << endl;
    return 0;
}