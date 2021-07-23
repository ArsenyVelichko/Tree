#ifndef TREE_GLGRAPHICSSCENE_H
#define TREE_GLGRAPHICSSCENE_H

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "../Painters/GLPainter.h"

class GLGraphicsScene {
public:
    virtual ~GLGraphicsScene();

    virtual void create(android_app* app, size_t width, size_t height) {}
    void update();

    void registerPainter(GLPainter* painter, const std::string& name);
    void addItem(GLGraphicsItem* item, const std::string& painterName);

private:
    using GLGraphicsContainer = std::pair<GLPainter*, std::vector<GLGraphicsItem*>>;
    std::map<std::string, GLGraphicsContainer> m_graphicsMap;
};

#endif //TREE_GLGRAPHICSSCENE_H
