#pragma once

#include "test.h"

namespace test{
    class TestClearColor: public Test
    {
        private:
            float m_ClearColor[4];
        public:
            TestClearColor();
            ~TestClearColor();

            void onUpdate(float deltaTime);
            void onRender();            
            void onImGuiRender();

    };
}