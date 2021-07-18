#ifndef TREE_MONOPAINTER_H
#define TREE_MONOPAINTER_H

#include <android_native_app_glue.h>

#include "GLPainter.h"
#include "../GLShaderProgram.h"

class MonoPainter : public GLPainter {
public:
    MonoPainter(AAssetManager* assetManager);

    void beginPaint() override;
    void endPaint() override;

    void drawItem(const GLGraphicsItem *item) const override;

    GLint location(ShaderVariable var) const override;

private:
    GLShaderProgram m_shaderProgram;
    bool m_isActive = false;
};

#endif //TREE_MONOPAINTER_H
