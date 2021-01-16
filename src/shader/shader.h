#pragma once
#include<string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_UniformLoctionCache;


        int GetUniformLocation(const std::string& name);
        unsigned int compileShader(unsigned int type, const std::string& source);
        void createShader(ShaderProgramSource source);
        ShaderProgramSource ParseShaders();

    public: 
        Shader(const std::string& filePath);
        ~Shader();

        void bind() const;
        void unbind() const;
        void setUniform1i(const std::string& name, int value);
        void setUniform1f(const std::string& name, float value);
        void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};