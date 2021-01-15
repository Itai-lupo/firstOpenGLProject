#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
    private:
        unsigned int m_RendererId;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout );
        void bind() const;
        void unbind() const;

};