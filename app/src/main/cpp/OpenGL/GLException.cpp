#include "GLException.h"

GLException::GLException(GLenum errorCode, const char* msg)
    : std::runtime_error(msg), m_errorCode(errorCode) {}