#include "shader.h"

#include <sstream>
#include <fstream>
#include <iostream>

std::string ReadShaderFile(const char *shader_file)
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

unsigned int BuildShader(GLenum shader_type, const char *shader_file_path)
{
    unsigned int shader_id;
    shader_id = glCreateShader(shader_type);
    std::string shader_source = ReadShaderFile(shader_file_path);
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

unsigned int BuildShaderProgram(const char *vertex_shader_path, const char *fragment_shader_path)
{
    unsigned int vertex_shader = BuildShader(GL_VERTEX_SHADER, vertex_shader_path);
    unsigned int frag_shader = BuildShader(GL_FRAGMENT_SHADER, fragment_shader_path);

    unsigned int shader_program;
    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);
    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    int success;
    char error_info[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, error_info);
        std::cout << "Error: Shader Compilation Failed\n"
                  << error_info << std::endl;
    }

    return shader_program;
}