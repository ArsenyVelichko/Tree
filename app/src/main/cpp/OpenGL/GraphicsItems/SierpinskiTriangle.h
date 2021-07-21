#ifndef TREE_SIERPINSKITRIANGLE_H
#define TREE_SIERPINSKITRIANGLE_H

#include <vector>

#include "GLGraphicsItem.h"

class SierpinskiTriangle : public GLGraphicsItem {
public:
    //TODO add max size parameter
    SierpinskiTriangle(const DoubleVec2& p1, const DoubleVec2& p2);
    ~SierpinskiTriangle();

    void enlarge();
    //TODO add reduce function

    void draw(const GLPainter *painter) const override;

private:
    void uploadToVBO();

    std::vector<FloatVec2> m_points;
    size_t m_currSize = 0;
    GLuint m_vbo;
};


#endif //TREE_SIERPINSKITRIANGLE_H
