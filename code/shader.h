#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>

std::string ReadShaderFile(const char *shader_file);

unsigned int BuildShader(GLenum shader_type, const char *shader_file_path);

unsigned int BuildShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path);

#endif  SHADER_H_