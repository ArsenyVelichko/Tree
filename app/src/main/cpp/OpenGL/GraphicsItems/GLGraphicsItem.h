#ifndef TREE_GLGRAPHICSITEM_H
#define TREE_GLGRAPHICSITEM_H

#include "../Defines.h"

class GLPainter;

class GLGraphicsItem {
public:
    virtual ~GLGraphicsItem() = default;

    virtual void draw(const GLPainter* painter) const = 0;

    void setTransform(const DoubleMat4& transform);
    DoubleMat4 transform() const;

private:
    DoubleMat4 m_transform = DoubleMat4(1.0);
};

inline void GLGraphicsItem::setTransform(const DoubleMat4& transform) {
    m_transform = transform;
}

inline DoubleMat4 GLGraphicsItem::transform() const {
    return m_transform;
}

#endif //TREE_GLGRAPHICSITEM_H
