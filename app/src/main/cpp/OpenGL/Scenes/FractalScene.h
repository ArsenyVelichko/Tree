#ifndef TREE_FRACTALSCENE_H
#define TREE_FRACTALSCENE_H

#include "GLGraphicsScene.h"
#include "../GraphicsItems/SierpinskiTriangle.h"

class FractalScene : public GLGraphicsScene {
public:
    void create(android_app* app, size_t width, size_t height) override;
    void touchEvent(AInputEvent* event);

private:
    size_t m_width;
    size_t m_height;

    SierpinskiTriangle* m_triangle = nullptr;
};


#endif //TREE_FRACTALSCENE_H
