#include "renderer.h"

#include <iostream>

using namespace std;


void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

void GLCheckError(const char *function, const char *file, int line)
{
    while(GLenum error = glGetError() != GL_NO_ERROR)
        cout << "[OpenGL error] (" << error << "): " << function << " " << file << ":" << line << endl;
    
}
