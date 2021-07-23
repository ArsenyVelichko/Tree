#ifndef TREE_LINE2D_H
#define TREE_LINE2D_H

#include <GLES3/gl32.h>

#include "GLGraphicsItem.h"

class Line2D : public GLGraphicsItem {
public:
    Line2D(const DoubleVec2& p1, const DoubleVec2& p2);
    ~Line2D();

    DoubleVec2 p1() const;
    DoubleVec2 p2() const;

    double length() const;
    DoubleVec2 toVec() const;

    void draw(const GLPainter *painter) const override;

private:
    FloatVec2 m_points[2];
    GLuint m_vbo;
};


#endif //TREE_LINE2D_H
