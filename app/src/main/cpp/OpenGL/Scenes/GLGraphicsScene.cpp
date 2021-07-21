#include "GLGraphicsScene.h"
#include "Log.h"

void GLGraphicsScene::registerPainter(GLPainter* painter, const std::string& name) {
    m_graphicsMap[name] = std::make_pair(painter, std::vector<GLGraphicsItem*>());
}

void GLGraphicsScene::addItem(GLGraphicsItem* item, const std::string& painterName) {
    if (m_graphicsMap.find(painterName) == m_graphicsMap.end()) {
        log_error("Painter not found");
        return;
    }

    m_graphicsMap[painterName].second.push_back(item);
}

void GLGraphicsScene::update() {
    for (auto& [key, value] : m_graphicsMap) {
        auto painter = value.first;

        painter->beginPaint();

        for (auto& item : value.second) {
            painter->drawItem(item);
        }

        painter->endPaint();
    }
}

GLGraphicsScene::~GLGraphicsScene() {
    for (auto&[key, value] : m_graphicsMap) {
        delete value.first;

        for (auto& item : value.second) {
            delete item;
        }
    }
}
