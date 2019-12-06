#include "shader.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertex_shader_path, const char* frag_shader_path)
{
    BuildShaderProgram(vertex_shader_path, frag_shader_path);
}

Shader::~Shader()
{
    glDeleteProgram(shader_program_id);
}

void Shader::Use()
{
    glUseProgram(shader_program_id);
}

void Shader::Reload(const char* vertex_shader_path, const char* frag_shader_path)
{
    unsigned int vertex_shader = BuildShader(GL_VERTEX_SHADER, vertex_shader_path);
    unsigned int frag_shader = BuildShader(GL_FRAGMENT_SHADER, frag_shader_path);

    unsigned int new_program_id = glCreateProgram();

    glAttachShader(new_program_id, vertex_shader);
    glAttachShader(new_program_id, frag_shader);
    glLinkProgram(new_program_id);
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    int success;
    char error_info[512];
    glGetProgramiv(new_program_id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetProgramInfoLog(new_program_id, 512, NULL, error_info);
        std::cout << "Error: Shader Program Compilation Failed\n" << error_info << std::endl;
        glDeleteProgram(new_program_id);
        return;
    }

    // Only delete the old program if the new program compiles properly
    glDeleteProgram(shader_program_id);
    shader_program_id = new_program_id;
    glUseProgram(shader_program_id);
}

void Shader::SetUniformFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shader_program_id, name.c_str()), value);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::ReadFile(const char *shader_file)
{
    std::stringstream shader_string;
    std::ifstream file(shader_file);
    if (!file)
    {
        std::cerr << "Error: Failed to open shader file"
                  << shader_file << std::endl;
        return shader_string.str();
    }

    file.ignore(std::numeric_limits<std::streamsize>::max());
    int size = file.gcount();

    if (size > 0x10000)
    {
        std::cerr << "Error: Shader file is way too big"
                  << shader_file << std::endl;
        return shader_string.str();
    }

    file.clear();
    file.seekg(0, std::ios_base::beg);

    shader_string << file.rdbuf();
    file.close();

    return shader_string.str();
}

unsigned int Shader::BuildShader(GLenum shader_type, const char *shader_file_path)
{
    unsigned int shader_id;
    shader_id = glCreateShader(shader_type);
    std::string shader_source = ReadFile(shader_file_path);
    const GLchar *shader_source_ptr = shader_source.c_str();
    glShaderSource(shader_id, 1, &shader_source_ptr, NULL);
    glCompileShader(shader_id);

    int success;
    char errorInfo[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader_id, 512, NULL, errorInfo);
        std::cout << "Error: Shader compilation failed\n"
                  << errorInfo << std::endl;
    }

    return shader_id;
}

void Shader::BuildShaderProgram(const char *vertex_shader_path, const char *fragment_shader_path)
{
    unsigned int vertex_shader = BuildShader(GL_VERTEX_SHADER, vertex_shader_path);
    unsigned int frag_shader = BuildShader(GL_FRAGMENT_SHADER, fragment_shader_path);

    shader_program_id = glCreateProgram();

    glAttachShader(shader_program_id, vertex_shader);
    glAttachShader(shader_program_id, frag_shader);
    glLinkProgram(shader_program_id);
    glUseProgram(shader_program_id);

    glDetachShader(shader_program_id, vertex_shader);
    glDetachShader(shader_program_id, frag_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    int success;
    char error_info[512];
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program_id, 512, NULL, error_info);
        std::cout << "Error: Shader Program Compilation Failed\n"
                  << error_info << std::endl;
    }
}