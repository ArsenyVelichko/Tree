#ifndef TREE_EGLEXCEPTION_H
#define TREE_EGLEXCEPTION_H

#include <exception>
#include <string>

#include <EGL/egl.h>

class EGLException : public std::exception {
public:
    explicit EGLException(const char* msg);

    const char* what() const noexcept override;
    EGLint errorCode() const;

private:
    std::string m_msg;
    EGLint m_errorCode;
};


#endif //TREE_EGLEXCEPTION_H
