#pragma once
#include <GL/glew.h>

#include "indexBuffer.h"
#include "vertexArray.h"

#include "shader.h"

#define GL_CALL(x) GLClearErrors();\
                    x;\
                    GLCheckError(#x, __FILE__, __LINE__);


void GLClearErrors();

void GLCheckError(const char *function, const char *file, int line);

class Renderer
{
    private:

    public:
        static void Draw(const VertexArray& va, const  IndexBuffer& ib, const  Shader& shader);
        static void Clear();
};