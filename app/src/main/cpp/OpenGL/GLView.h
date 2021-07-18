#ifndef TREE_GLVIEW_H
#define TREE_GLVIEW_H

#include <vector>
#include <string>
#include <map>

#include <android_native_app_glue.h>
#include <GLES3/gl32.h>
#include <EGL/egl.h>

#include "../IView.h"
#include "Painters/GLPainter.h"

class GLView : public IView {
public:
    explicit GLView(android_app* app);
    ~GLView();

    void init() override;
    void update() override;
    void term() override;

    void registerPainter(GLPainter* painter, const std::string& name);
    void addItem(GLGraphicsItem* item, const std::string& painterName);

private:
    bool m_isInit = false;

    android_app* m_app;

    EGLDisplay m_display = EGL_NO_DISPLAY;
    EGLSurface m_surface = EGL_NO_SURFACE;
    EGLContext m_context = EGL_NO_CONTEXT;

    EGLint m_width;
    EGLint m_height;

    using GLGraphicsContainer = std::pair<GLPainter*, std::vector<GLGraphicsItem*>>;
    std::map<std::string, GLGraphicsContainer> m_graphicsMap;
};

#endif //TREE_GLVIEW_H
