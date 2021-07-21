#include <GLES3/gl32.h>

#include "Log.h"
#include "../GLException.h"
#include "../Painters/GLPainter.h"
#include "Line2D.h"

Line2D::Line2D(const DoubleVec2& p1, const DoubleVec2& p2) : m_points{ p1, p2 }{
    glGenBuffers(1, &m_vbo);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw GLException(err, "Buffer creation failed");
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line2D::draw(const GLPainter* painter) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    GLint positionLoc = painter->location(ShaderVariable::Position);
    if (positionLoc == -1) {
        log_error("Position location not found");
        return;
    }

    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(FloatVec2), nullptr);
    glEnableVertexAttribArray(positionLoc);

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Line2D::~Line2D() {
    glDeleteBuffers(1, &m_vbo);
}

DoubleVec2 Line2D::firstPoint() const {
    return m_points[0];
}

DoubleVec2 Line2D::secondPoint() const {
    return m_points[1];
}

double Line2D::length() const {
    return glm::length(toVec());
}

DoubleVec2 Line2D::toVec() const {
    return m_points[1] - m_points[0];
}
