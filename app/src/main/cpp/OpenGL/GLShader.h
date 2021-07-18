#ifndef TREE_GLSHADER_H
#define TREE_GLSHADER_H

#include <GLES3/gl32.h>

#include "../AssetHandler.h"

class GLShader {
public:
    explicit GLShader(GLenum shaderType);
    ~GLShader();

    bool compile(const AssetHandler& asset);

    GLenum shaderType() const;
    bool isCompiled() const;
    GLuint shaderId() const;

private:
    GLenum m_shaderType;
    GLuint m_shaderId;
    GLint m_isCompiled = GL_FALSE;
};

inline GLenum GLShader::shaderType() const {
    return m_shaderType;
}

inline bool GLShader::isCompiled() const {
    return m_isCompiled;
}

inline GLuint GLShader::shaderId() const {
    return m_shaderId;
}

#endif //TREE_GLSHADER_H
