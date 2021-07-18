#include <stdexcept>
#include <vector>

#include "Log.h"
#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram() : m_programId(glCreateProgram()) {
    if (m_programId == 0) {
        throw std::runtime_error("Shader program was not created");
    }
}

bool GLShaderProgram::link() {
    glLinkProgram(m_programId);

    GLint isLinked;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(m_programId, maxLength, &maxLength, &errorLog[0]);

        log_error("Program linking failed: %s", errorLog.data());

        return false;
    }

    return true;
}

void GLShaderProgram::attachShader(const GLShader& shader) {
    if (!shader.isCompiled()) {
        log_error("Shader is not compiled");
        return;
    }

    glAttachShader(m_programId, shader.shaderId());
}

GLShaderProgram::~GLShaderProgram() {
    glDeleteProgram(m_programId);
}
