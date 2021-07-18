#ifndef TREE_GLPAINTER_H
#define TREE_GLPAINTER_H

#include <memory>
#include <glm/matrix.hpp>

#include "../GLShader.h"
#include "../GraphicsItems/GLGraphicsItem.h"

enum class ShaderVariable {
    Position,
    TexCoordinate,
    MVPMatrix,
};

class GLPainter {
public:
    virtual ~GLPainter() = default;

    virtual void beginPaint() = 0;
    virtual void endPaint() = 0;

    virtual void drawItem(const GLGraphicsItem* item) const = 0;
    virtual GLint location(ShaderVariable var) const { return -1; }
};

#endif //TREE_GLPAINTER_H
