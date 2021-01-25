#include <iostream>
#include <string>

using namespace std;

#include "handleOpenGlErrors.h"

void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

void GLCheckError(const char *function, const char *file, int line)
{
    GLenum error;
    while((error = glGetError()) != GL_NO_ERROR)
        cout << "[OpenGL error] (" << error << "): " << function << " " << file << ":" << line << endl;
    
}
