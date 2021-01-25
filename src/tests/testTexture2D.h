#pragma once

#include "test.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"


namespace test{
    class TestTexture2D: public Test
    {
        private:
            glm::mat4 proj;
            Shader shader;
            glm::vec3 translation;
            glm::mat4 view;
            VertexArray va;
            IndexBuffer *ib;
            VertexBuffer *vb;
            Texture texture;
        public:
            TestTexture2D();
            ~TestTexture2D();

            void onUpdate(float deltaTime);
            void onRender();            
            void onImGuiRender();

    };
}