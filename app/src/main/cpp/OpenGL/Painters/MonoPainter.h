#ifndef TREE_MONOPAINTER_H
#define TREE_MONOPAINTER_H

#include <android_native_app_glue.h>

#include "GLPainter.h"
#include "../GLShaderProgram.h"

class MonoPainter : public GLPainter {
public:
    MonoPainter(AAssetManager* assetManager);

    void setColor(const Color& color);

    void beginPaint() override;
    void endPaint() override;

    void drawItem(const GLGraphicsItem* item) override;
    GLint attribLocation(ShaderAttribute var) const override;

private:
    void uploadTransform(const DoubleMat4& itemTransform);
    void uploadColor();

    GLShaderProgram m_shaderProgram;
    Color m_color = Color(0.0f);
    bool m_isActive = false;
};

inline void MonoPainter::setColor(const Color& color) {
    m_color = color;
}

#endif //TREE_MONOPAINTER_H
