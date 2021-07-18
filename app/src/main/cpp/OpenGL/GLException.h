#ifndef TREE_GLEXCEPTION_H
#define TREE_GLEXCEPTION_H

#include <stdexcept>
#include <GLES3/gl32.h>

class GLException : std::runtime_error {
public:
    GLException(GLenum errorCode, const char* msg);

    GLenum errorCode() const;

private:
    GLenum m_errorCode;
};

inline GLenum GLException::errorCode() const {
    return m_errorCode;
}
#endif //TREE_GLEXCEPTION_H
