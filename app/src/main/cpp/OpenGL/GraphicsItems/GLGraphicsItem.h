#ifndef TREE_GLGRAPHICSITEM_H
#define TREE_GLGRAPHICSITEM_H

#include "../Geometry.h"

class GLPainter;

class GLGraphicsItem {
public:
    virtual ~GLGraphicsItem() = default;

    virtual void draw(const GLPainter* painter) const = 0;
};

#endif //TREE_GLGRAPHICSITEM_H
