#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const char* vertex_shader_path, const char* frag_shader_path);
    ~Shader();

    void Use();
    void Reload(const char* vertex_shader_path, const char* frag_shader_path);
    void SetUniformFloat(const std::string &name, float value) const;
    void SetUniformMat4(const std::string& name, glm::mat4 value) const;

private:
    std::string ReadFile(const char *shader_file);
    unsigned int BuildShader(GLenum shader_type, const char *shader_file_path);
    void BuildShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path);
    
    unsigned int shader_program_id;
};
#endif  //SHADER_H_