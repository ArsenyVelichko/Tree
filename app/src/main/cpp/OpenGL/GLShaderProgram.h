#ifndef TREE_GLSHADERPROGRAM_H
#define TREE_GLSHADERPROGRAM_H

#include <GLES3/gl32.h>

#include "GLShader.h"

class GLShaderProgram {
public:
    GLShaderProgram();
    ~GLShaderProgram();

    void attachShader(const GLShader& shader);

    bool link();
    void bind();
    void release();

    GLint attribLocation(const char* name) const;
    GLint uniformLocation(const char* name) const;

private:
    GLuint m_programId;
};

inline void GLShaderProgram::bind() {
    glUseProgram(m_programId);
}

inline void GLShaderProgram::release() {
    glUseProgram(0);
}

inline GLint GLShaderProgram::attribLocation(const char* name) const {
    return glGetAttribLocation(m_programId, name);
}

inline GLint GLShaderProgram::uniformLocation(const char* name) const {
    return glGetUniformLocation(m_programId, name);
}


#endif //TREE_GLSHADERPROGRAM_H
