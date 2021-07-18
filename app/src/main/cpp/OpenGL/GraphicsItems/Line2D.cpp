#include <GLES3/gl32.h>
#include <Log.h>

#include "../GLException.h"
#include "../Painters/GLPainter.h"
#include "Line2D.h"

Line2D::Line2D(glm::vec2 firstPoint, glm::vec2 secondPoint) {
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glm::vec2 vertices[] = { firstPoint, secondPoint };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw GLException(err, "Buffer creation failed");
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line2D::draw(const GLPainter* painter) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    GLint positionLoc = painter->location(ShaderVariable::Position);
    if (positionLoc == -1) {
        log_error("Position location not found");
        return;
    }

    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), nullptr);
    glEnableVertexAttribArray(positionLoc);

    glDrawArrays(GL_LINES, 0, 2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Line2D::~Line2D() {
    glDeleteBuffers(1, &m_vbo);
}
