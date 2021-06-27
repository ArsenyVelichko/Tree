#include <memory>
#include <Log.h>
#include <EGLException.h>

#include "TreeView.h"

TreeView::TreeView(android_app* app) : m_app(app) {}

void TreeView::init() {
    if (m_isInit) { return; }

    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    EGLint format;
    EGLint numConfigs;
    EGLConfig config = nullptr;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (!eglInitialize(m_display, nullptr, nullptr)) {
        throw EGLException("EGL display initialization failed");
    }

    eglChooseConfig(m_display, attribs, &config, 1, &numConfigs);
    if (numConfigs == 0) {
        throw EGLException("No EGL config have been chosen");
    }

    eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

    //Set pixel format to android window buffer
    ANativeWindow_setBuffersGeometry(m_app->window, 0, 0, format);

    m_surface = eglCreateWindowSurface(m_display, config, m_app->window, nullptr);
    if (m_surface == EGL_NO_SURFACE) {
        throw EGLException("Surface creation failed");
    }

    m_context = eglCreateContext(m_display, config, nullptr, nullptr);
    if (m_context == EGL_NO_CONTEXT) {
        throw EGLException("Context creation failed");
    }

    if (!eglMakeCurrent(m_display, m_surface, m_surface, m_context)) {
        throw EGLException("Unable make context current");
    }

    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);

    // Check openGL on the system
    auto openglInfo = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};
    for (auto name : openglInfo) {
        auto info = glGetString(name);
        log_info("OpenGL Info: %s", info);
    }

    m_isInit = true;
}

void TreeView::update() {
    if (!m_isInit) { return; }

    glClearColor(0.3f, 0.5f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!eglSwapBuffers(m_display, m_surface)) {
        log_error("Swap buffers error");
    }
}

void TreeView::term() {
    if (m_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (m_context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_display, m_context);
            m_context = EGL_NO_CONTEXT;
        }

        if (m_surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_display, m_surface);
            m_surface = EGL_NO_SURFACE;
        }

        eglTerminate(m_display);
        m_display = EGL_NO_DISPLAY;
    }

    m_isInit = false;
}
