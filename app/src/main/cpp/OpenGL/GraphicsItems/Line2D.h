#ifndef TREE_LINE2D_H
#define TREE_LINE2D_H

#include <glm/vec2.hpp>

#include "GLGraphicsItem.h"

class Line2D : public GLGraphicsItem {
public:
    Line2D(glm::vec2 firstPoint, glm::vec2 secondPoint);
    ~Line2D();

    void draw(const GLPainter *painter) const override;

private:
    GLuint m_vbo;
};


#endif //TREE_LINE2D_H
