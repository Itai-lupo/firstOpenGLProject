#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "renderer.h"

#include "tests/test.h"
#include "tests/testClearColor.h"
#include "tests/testTexture2D.h"

#include "tests/testMenu.h"

using namespace std;

int initWindow( GLFWwindow*& window);
void setWindowHints();
void initImGui(GLFWwindow* window);
void registerTests(test::testMenu& menu);
void gameLoop( GLFWwindow* window, test::testMenu& menu, test::Test *&test);
void renderTest(bool isTestEnabeld, test::Test *&test);
void renderImGui(test::testMenu& menu, test::Test *& test);
void destroyImGui();

int main(void)
{
    GLFWwindow* window;

    if( initWindow( window) != 0)
        return -1;

    initImGui(window);

    test::Test *test = new test::TestClearColor();

    test::testMenu menu(&test);
    
    registerTests(menu);
    
    gameLoop( window, menu, test);

    glfwTerminate();

    cout << "end" << endl;
    return 0;
}

int initWindow( GLFWwindow*& window)
{
    if (!glfwInit())
        return -1;

    setWindowHints();

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

    return 0;
}

void setWindowHints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void initImGui(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
}

void registerTests(test::testMenu& menu)
{
    menu.registerTest<test::TestClearColor>("clear color test");
    menu.registerTest<test::TestTexture2D>("texture2D test2");
}

void gameLoop( GLFWwindow* window, test::testMenu& menu, test::Test *& test)
{
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        Renderer::Clear(); 
        renderTest(menu.isTestEnabeld(), test);

        renderImGui(menu, test);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

}

void renderTest(bool isTestEnabeld, test::Test *&test)
{
    if(isTestEnabeld){
        test->onUpdate(0.0f);
        test->onRender();
    }
}

void renderImGui(test::testMenu& menu, test::Test *& test)
{
    ImGui::NewFrame();
    if(menu.isTestEnabeld())
        test->onImGuiRender();
            
    menu.onImGuiRender();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void destroyImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
