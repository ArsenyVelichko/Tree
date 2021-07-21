#include <GLES3/gl32.h>

#include <glm/vec2.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Log.h"
#include "../Painters/GLPainter.h"
#include "SierpinskiTriangle.h"
#include "../GLException.h"

SierpinskiTriangle::SierpinskiTriangle(const DoubleVec2& p1, const DoubleVec2& p2) {
    m_points.emplace_back(p1);
    m_points.emplace_back(p2);

    glGenBuffers(1, &m_vbo);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw GLException(err, "Buffer creation failed");
    }

    uploadToVBO();
}

SierpinskiTriangle::~SierpinskiTriangle() {
    glDeleteBuffers(1, &m_vbo);
}

void SierpinskiTriangle::enlarge() {
    size_t newSize = 3 * m_points.size() - 2;
    std::vector<FloatVec2> newPoints(newSize);

    double rotateAngle = m_currSize % 2 ? -60.0 : 60.0;
    rotateAngle = glm::radians(rotateAngle);

    for (size_t i = 0; i < m_points.size() - 1; i++) {
        DoubleVec2 p1 = m_points[i];
        DoubleVec2 p4 = m_points[i + 1];

        DoubleVec2 diff = p4 - p1;
        diff /= 2.0;

        DoubleVec2 p2 = p1 + glm::rotate(diff, rotateAngle);
        DoubleVec2 p3 = p2 + diff;

        size_t beginIdx = 3 * i;
        newPoints[beginIdx] = p1;
        newPoints[beginIdx + 1] = p2;
        newPoints[beginIdx + 2] = p3;

        rotateAngle *= -1.0f;
    }
    newPoints.back() = m_points.back();
    m_points = newPoints;

    uploadToVBO();
    m_currSize++;
}

void SierpinskiTriangle::draw(const GLPainter* painter) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    GLint positionLoc = painter->location(ShaderVariable::Position);
    if (positionLoc == -1) {
        log_error("Position location not found");
        return;
    }

    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(FloatVec2), nullptr);
    glEnableVertexAttribArray(positionLoc);

    glDrawArrays(GL_LINE_STRIP, 0, m_points.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SierpinskiTriangle::uploadToVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    size_t sizeInBytes = m_points.size() * sizeof(FloatVec2);
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, m_points.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
