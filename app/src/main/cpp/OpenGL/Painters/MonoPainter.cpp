#include <stdexcept>
#include <string>

#include "Log.h"
#include "MonoPainter.h"
#include "../GLShader.h"
#include "../AssetHandler.h"

MonoPainter::MonoPainter(AAssetManager* assetManager) {
    AssetHandler vertexAsset(assetManager, "shaders/Mono.vert", AASSET_MODE_BUFFER);
    GLShader vertexShader(GL_VERTEX_SHADER);
    vertexShader.compile(vertexAsset);

    AssetHandler fragmentAsset(assetManager, "shaders/Mono.frag", AASSET_MODE_BUFFER);
    GLShader fragmentShader(GL_FRAGMENT_SHADER);
    fragmentShader.compile(fragmentAsset);

    m_shaderProgram.attachShader(vertexShader);
    m_shaderProgram.attachShader(fragmentShader);
    m_shaderProgram.link();
}

void MonoPainter::beginPaint() {
    m_shaderProgram.bind();
    m_isActive = true;
}

void MonoPainter::endPaint() {
    m_shaderProgram.release();
    m_isActive = false;
}

void MonoPainter::drawItem(const GLGraphicsItem* item) {
    if (!m_isActive) {
        log_error("Call beginPaint before drawing");
        return;
    }

    uploadColor();
    uploadTransform(item->transform());
    item->draw(this);
}

GLint MonoPainter::attribLocation(ShaderAttribute var) const {
    GLint loc;

    switch (var) {
        case ShaderAttribute::Position:
            loc = m_shaderProgram.attribLocation("position");
            break;

        default:
            loc = -1;
            break;
    }

    return loc;
}

void MonoPainter::uploadTransform(const DoubleMat4& itemTransform) {
    GLint mvpMatLoc = m_shaderProgram.uniformLocation("mvpMat");
    FloatMat4 mvpMatrix = transform() * itemTransform;
    glUniformMatrix4fv(mvpMatLoc, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
}

void MonoPainter::uploadColor() {
    GLint colorLoc = m_shaderProgram.uniformLocation("color");
    glUniform4fv(colorLoc, 1, glm::value_ptr(m_color));
}
