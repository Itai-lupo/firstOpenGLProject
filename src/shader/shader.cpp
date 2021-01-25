#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtx/string_cast.hpp>


#include "handleOpenGlErrors.h"


using namespace std;



Shader::Shader(const string& filePath): m_FilePath(filePath)
{
    ShaderProgramSource source = ParseShaders();
    createShader(source);

    GL_CALL(glUseProgram(m_RendererID));

}

Shader::~Shader()
{
    GL_CALL(glDeleteProgram(m_RendererID));
}


ShaderProgramSource Shader::ParseShaders()
{
    ifstream stream(m_FilePath);

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

void Shader::createShader(ShaderProgramSource source)
{
    GL_CALL(m_RendererID = glCreateProgram());
    GL_CALL(unsigned int vs = compileShader(GL_VERTEX_SHADER, source.VertexSource);)
    GL_CALL(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.FragmentSource));

    GL_CALL(glAttachShader(m_RendererID, vs));
    GL_CALL(glAttachShader(m_RendererID, fs));
    GL_CALL(glLinkProgram(m_RendererID));
    GL_CALL(glValidateProgram(m_RendererID));

    GL_CALL(glDeleteShader(vs));
    GL_CALL(glDeleteShader(fs));
}

unsigned int Shader::compileShader(unsigned int type, const string& source)
{
    unsigned int id;
    GL_CALL(id = glCreateShader(type));
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



void Shader::bind() const
{
    GL_CALL(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GL_CALL(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}


void Shader::setUniform1i(const std::string& name, int value)
{
    GL_CALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value)
{
    GL_CALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::setUniformMat4f(const std::string& name,  glm::mat4& value)
{   
    GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
}


int Shader::GetUniformLocation(const std::string& name)
{
    if(m_UniformLoctionCache.find(name) != m_UniformLoctionCache.end()) 
        return m_UniformLoctionCache[name];

    GL_CALL(m_UniformLoctionCache[name] = glGetUniformLocation(m_RendererID, name.c_str()));

    return m_UniformLoctionCache[name];
}

