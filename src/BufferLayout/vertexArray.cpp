#include "vertexArray.h"
#include "renderer.h"

#include <iostream>


VertexArray::VertexArray()
{

    GL_CALL(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray()
{
    GL_CALL(glDeleteVertexArrays(1, &m_RendererId));
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout )
{
    bind();
    const auto& elements = layout.getElements();

    vb.bind();
    unsigned long i = 0, offset = 0;
    for(const auto& element : elements)
    {
        GL_CALL(glEnableVertexAttribArray(i));
        GL_CALL(glVertexAttribPointer(i, element.count, element.type, element.normalized,  layout.GetStride(), (const void*)offset));
        offset += element.count * element.GetSizeOfType();
        i++;

    }
}

void VertexArray::bind() const
{
    GL_CALL(glBindVertexArray(m_RendererId));
}

void VertexArray::unbind() const
{
    GL_CALL(glBindVertexArray(0));
}

