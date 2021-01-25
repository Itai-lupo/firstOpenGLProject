#pragma once

#include "test.h"

#include <string>
#include <vector>
#include <functional>


namespace test{
    class testMenu
    {
        private:
            Test ** loadedTest;
            bool testEnabeld;

            void setLoadedTest(Test *newTest);

            std::vector<std::pair<std::string, std::function<Test*()>>> tests;


        public:
            testMenu(Test ** loadedTest);
            ~testMenu();
        
            void onImGuiRender();
            bool isTestEnabeld() const { return testEnabeld; }

            template <typename T>
            void registerTest(const std::string& name)
            {
                tests.push_back(std::make_pair(name, [](){ return new T();}));
            }

    };
}