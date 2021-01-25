#include "renderer.h"

#include <iostream>

using namespace std;


void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

void GLCheckError(const char *function, const char *file, int line)
{
    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR)
        cout << "[OpenGL error] (" << error << "): " << function << " " << file << ":" << line << endl;
    
}


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
