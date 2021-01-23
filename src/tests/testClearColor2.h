#pragma once

#include "test.h"

namespace test{
    class TestClearColor2: public Test
    {
        private:
            float m_ClearColor[4];
        public:
            TestClearColor2();
            ~TestClearColor2();

            void onUpdate(float deltaTime);
            void onRender();            
            void onImGuiRender();

    };
}