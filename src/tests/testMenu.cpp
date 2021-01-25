#include "testMenu.h"

#include <GL/glew.h>
#include "renderer.h"
#include "imgui/imgui.h"


namespace test{
    testMenu::testMenu(Test ** loadedTest)
        :loadedTest(loadedTest), testEnabeld(false)
    {

    }

    testMenu::~testMenu()
    {
        if( *loadedTest != nullptr )
            free(*loadedTest);
    }

    void testMenu::onImGuiRender()
    {
        if(!testEnabeld){
            for(auto& test: tests)
                if(ImGui::Button(test.first.c_str()))
                    setLoadedTest( test.second());
        }
        else
        {
            if(ImGui::Button("back", {200, 30}))
                testEnabeld = false;
        }

    }

    void testMenu::setLoadedTest(Test *newTest)
    {
        *loadedTest = newTest;
        testEnabeld = true;
    }


}