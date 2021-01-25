#include "indexBuffer.h"

#include "handleOpenGlErrors.h"


IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
    :m_Count(count)
{
    GL_CALL(glGenBuffers(1, &m_RendererID));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}


IndexBuffer::~IndexBuffer()
{
    GL_CALL(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
