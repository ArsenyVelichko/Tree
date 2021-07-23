#ifndef TREE_GLPAINTER_H
#define TREE_GLPAINTER_H

#include <memory>

#include "../Defines.h"
#include "../GLShader.h"
#include "../GraphicsItems/GLGraphicsItem.h"

enum class ShaderAttribute {
    Position,
    TexCoordinate,
};

class GLPainter {
public:
    virtual ~GLPainter() = default;

    virtual void beginPaint() = 0;
    virtual void endPaint() = 0;

    virtual void drawItem(const GLGraphicsItem* item) = 0;
    virtual GLint attribLocation(ShaderAttribute attr) const { return -1; }

    void setTransform(const DoubleMat4& transform);
    DoubleMat4 transform() const;

private:
    DoubleMat4 m_transform = DoubleMat4(1.0);
};

inline void GLPainter::setTransform(const DoubleMat4& transform) {
    m_transform = transform;
}

inline DoubleMat4 GLPainter::transform() const {
    return m_transform;
}

#endif //TREE_GLPAINTER_H
