#include "renderer.h"
#include "handleOpenGlErrors.h"

#include <iostream>

using namespace std;


void Renderer::Draw(const VertexArray& va, const  IndexBuffer& ib, const  Shader& shader)
{
    va.bind();
    ib.bind();
    shader.bind();
    GL_CALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
