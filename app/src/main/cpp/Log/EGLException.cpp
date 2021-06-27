#include "EGLException.h"

EGLException::EGLException(const char* msg)
    : m_msg(msg), m_errorCode(eglGetError()) {}

const char* EGLException::what() const noexcept {
    return m_msg.c_str();
}

EGLint EGLException::errorCode() const {
    return m_errorCode;
}
