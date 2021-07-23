#ifndef TREE_SIERPINSKITRIANGLE_H
#define TREE_SIERPINSKITRIANGLE_H

#include <vector>

#include "GLGraphicsItem.h"

class SierpinskiTriangle : public GLGraphicsItem {
public:
    SierpinskiTriangle(const DoubleVec2& p1, const DoubleVec2& p2, size_t maxSize = 10);
    ~SierpinskiTriangle();

    void enlarge();
    void reduce();

    void draw(const GLPainter *painter) const override;

private:
    void uploadToVBO();

    std::vector<FloatVec2> m_points;
    size_t m_currSize = 0;
    size_t m_maxSize;
    GLuint m_vbo;
};


#endif //TREE_SIERPINSKITRIANGLE_H
