#pragma once
#include <GL/glew.h>

#include "indexBuffer.h"
#include "vertexArray.h"

#include "shader.h"

class Renderer
{
    private:

    public:
        static void Draw(const VertexArray& va, const  IndexBuffer& ib, const  Shader& shader);
        static void Clear();
};