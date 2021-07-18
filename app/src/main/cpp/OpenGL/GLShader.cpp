#include <vector>

#include "Log.h"
#include "GLShader.h"

GLShader::GLShader(GLenum shaderType) : m_shaderType(shaderType) {
    m_shaderId = glCreateShader(shaderType);

    if (m_shaderId == 0) {
        throw std::runtime_error("Shader was not created");
    }
}

bool GLShader::compile(const AssetHandler& asset) {
    auto sourceCode = static_cast<const GLchar*>(asset.buffer());
    GLint len = asset.length();

    glShaderSource(m_shaderId, 1, &sourceCode, &len);
    glCompileShader(m_shaderId);

    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &m_isCompiled);
    if (m_isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(m_shaderId, maxLength, &maxLength, &errorLog[0]);

        log_error("Shader compile failed: %s", errorLog.data());

        return false;
    }

    return true;
}

GLShader::~GLShader() {
    glDeleteShader(m_shaderId);
}


