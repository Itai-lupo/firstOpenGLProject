#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GL_CALL(x) GLClearErrors;\
                    x;\
                    GLCheckError(#x, __FILE__, __LINE__);

using namespace std;

static void GLClearErrors()
{
    while(glGetError() != GL_NO_ERROR);
}

static void GLCheckError(const char *function, const char *file, int line){
    while(GLenum error = glGetError() != GL_NO_ERROR)
        cout << "[OpenGL error] (" << error << "): " << function << " " << file << ":" << line << endl;
    
}

struct ShaderProgramSource
{
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource ParseShaders(const string& filePath)
{
    ifstream stream(filePath);

    enum class ShaderType{
        NONE = -1,
        vertex = 0,
        fragment = 1
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)){
        if(line.find("#shader") != string::npos)
        {
            if(line.find("vertex") != string::npos)
                type = ShaderType::vertex;
            else if(line.find("fragment") != string::npos)
                type = ShaderType::fragment;

        }
        else if((int)type >= 0)
        {
            ss[(int)type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader(unsigned int type, const string& source)
{
    GL_CALL(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GL_CALL(glShaderSource(id, 1, &src, nullptr));
    GL_CALL(glCompileShader(id));

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GL_CALL(glGetShaderInfoLog(id, length, &length, message));
        cout << "falid to compile "<< ( type == GL_VERTEX_SHADER ? "vertex": "fragment" ) << " shader" << endl;
        cout << message << endl;
        GL_CALL(glDeleteShader(id));
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
{
    GL_CALL(unsigned int program = glCreateProgram());
    GL_CALL(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);)
    GL_CALL(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GL_CALL(glAttachShader(program, vs));
    GL_CALL(glAttachShader(program, fs));
    GL_CALL(glLinkProgram(program));
    GL_CALL(glValidateProgram(program));

    GL_CALL(glDeleteShader(vs));
    GL_CALL(glDeleteShader(fs));

    return program;

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        std::cout << "error" <<endl;

    float postions[8] = { 
        -0.5f,  -0.5,
        0.5f,   -0.5f,
        0.5f,   0.5f,
        -0.5f,   0.5f,
     };

    unsigned int indices[6] = {
         0, 1, 2,
         2, 3, 0
     };

    unsigned int buffer; 
    GL_CALL(glGenBuffers(1, &buffer));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), postions, GL_STATIC_DRAW));

    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, false, 2*sizeof(float), 0));


    unsigned int ibo; 
    GL_CALL(glGenBuffers(1, &ibo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));


    ShaderProgramSource source = ParseShaders("res/shaders/Basic.shader");


    unsigned int shader =  CreateShader(source.VertexSource, source.FragmentSource);


    GL_CALL(glUseProgram(shader));

    GL_CALL(int u_Color_loction = glGetUniformLocation(shader, "u_Color"));
    GL_CALL(glUniform4f(u_Color_loction, 0.0f, 0.0f, 1.0f, 1.0f));

    /* Loop until the user closes the window */
    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        
        i = (i + 50) % 1000;
        GL_CALL(glUniform4f(u_Color_loction, ((float)((i + 300)%1000))/1000, ((float)((i + 600)%1000))/1000, ((float)((i + 900)%1000))/1000, 1.0f));
        /* Render here */
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

        GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GL_CALL(glDeleteProgram(shader));
    glfwTerminate();


    cout << "end" << endl;
    return 0;
}