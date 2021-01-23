#include "testClearColor2.h"

#include <GL/glew.h>
#include "renderer.h"
#include "imgui/imgui.h"

namespace test{
    TestClearColor2::TestClearColor2()
        :m_ClearColor { 1.0f, 0.1f, 0.5f, 1.0f}
    {

    }

    TestClearColor2::~TestClearColor2()
    {

    }

    void TestClearColor2::onUpdate(float deltaTime)
    {

    }

    void TestClearColor2::onRender()
    {
        GL_CALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }   

    void TestClearColor2::onImGuiRender()
    {
        ImGui::ColorEdit4("clear color", m_ClearColor);
        ImGui::ColorEdit4("clear color", m_ClearColor);
    }
}