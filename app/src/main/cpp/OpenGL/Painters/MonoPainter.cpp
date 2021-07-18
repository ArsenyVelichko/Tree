#include <stdexcept>
#include <string>

#include <glm/gtc/type_ptr.hpp>

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

    //TODO add transform functionality to painters
    glm::mat4 m(1.0f);
    GLint mvpMatrixLoc = location(ShaderVariable::MVPMatrix);
    glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(m));

    m_isActive = true;
}

void MonoPainter::endPaint() {
    m_shaderProgram.release();
    m_isActive = false;
}

void MonoPainter::drawItem(const GLGraphicsItem* item) const {
    if (!m_isActive) {
        log_error("Call beginPaint before drawing");
        return;
    }

    item->draw(this);
}

GLint MonoPainter::location(ShaderVariable var) const {
    GLint loc;

    switch (var) {
        case ShaderVariable::Position:
            loc = m_shaderProgram.attribLocation("position");
            break;

        case ShaderVariable::MVPMatrix:
            loc = m_shaderProgram.uniformLocation("mvpMatrix");
            break;

        default:
            loc = -1;
            break;
    }

    return loc;
}
