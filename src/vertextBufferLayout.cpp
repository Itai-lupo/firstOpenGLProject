#include "vertexBufferLayout.h"

void VertexBufferLayout::push(VertexBufferElement ElementToPush)
{
    m_Elements.push_back(ElementToPush);
    m_Stride += sizeof(ElementToPush.GetSizeOfType()) * ElementToPush.count;
}
