#include <memory>

#include "Log.h"
#include "GLView.h"
#include "GraphicsItems/Line2D.h"
#include "GraphicsItems/SierpinskiTriangle.h"
#include "Painters/MonoPainter.h"

GLView::GLView(android_app* app) : m_app(app) {}

void GLView::init() {
    if (m_isInit) { return; }

    const EGLint displayAttribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };

    const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    EGLint format;
    EGLint numConfigs;
    EGLConfig config = nullptr;

    m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    if (!eglInitialize(m_display, nullptr, nullptr)) {
        log_error("EGL display initialization failed");
        return;
    }

    eglChooseConfig(m_display, displayAttribs, &config, 1, &numConfigs);
    if (numConfigs == 0) {
        log_error("No EGL config have been chosen");
        return;
    }

    eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

    //Set pixel format to android window buffer
    ANativeWindow_setBuffersGeometry(m_app->window, 0, 0, format);

    m_surface = eglCreateWindowSurface(m_display, config, m_app->window, nullptr);
    if (m_surface == EGL_NO_SURFACE) {
        log_error("Surface creation failed");
        return;
    }

    m_context = eglCreateContext(m_display, config, nullptr, contextAttribs);
    if (m_context == EGL_NO_CONTEXT) {
        log_error("Context creation failed");
        return;
    }

    if (!eglMakeCurrent(m_display, m_surface, m_surface, m_context)) {
        log_error("Unable make context current");
        return;
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

    if (m_scene) {
        m_scene->create(m_app);
    }

    m_isInit = true;
}

void GLView::update() {
    if (!m_isInit) { return; }

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_scene->update();

    if (!eglSwapBuffers(m_display, m_surface)) {
        log_error("Swap buffers error");
    }
}

void GLView::term() {
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

void GLView::setScene(GLGraphicsScene* scene) {
    //TODO Add ability to change scene after initialization
    if (m_isInit) {
        log_warning("View already initialized");
        return;
    }

    delete m_scene;
    m_scene = scene;
}

GLView::~GLView() {
    delete m_scene;
}
