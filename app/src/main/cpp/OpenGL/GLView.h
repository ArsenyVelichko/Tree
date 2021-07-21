#ifndef TREE_GLVIEW_H
#define TREE_GLVIEW_H

#include <android_native_app_glue.h>
#include <GLES3/gl32.h>
#include <EGL/egl.h>

#include "../IView.h"
#include "Scenes/GLGraphicsScene.h"

class GLView : public IView {
public:
    explicit GLView(android_app* app);
    ~GLView();

    void setScene(GLGraphicsScene* scene);

    void init() override;
    void update() override;
    void term() override;

private:
    bool m_isInit = false;

    android_app* m_app;
    GLGraphicsScene* m_scene = nullptr;

    EGLDisplay m_display = EGL_NO_DISPLAY;
    EGLSurface m_surface = EGL_NO_SURFACE;
    EGLContext m_context = EGL_NO_CONTEXT;

    EGLint m_width;
    EGLint m_height;
};

#endif //TREE_GLVIEW_H
