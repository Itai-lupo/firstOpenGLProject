#pragma once


namespace test{
    class Test{
        public:

            virtual void onUpdate(float deltaTime) = 0;
            virtual void onRender() = 0;            
            virtual void onImGuiRender() = 0;


    };
}