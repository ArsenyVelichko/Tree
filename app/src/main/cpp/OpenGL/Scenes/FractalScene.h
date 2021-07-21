#ifndef TREE_FRACTALSCENE_H
#define TREE_FRACTALSCENE_H

#include "GLGraphicsScene.h"
#include "../GraphicsItems/SierpinskiTriangle.h"

class FractalScene : public GLGraphicsScene {
public:
    void create(android_app* app) override;
    void touchEvent(AInputEvent* event);

private:
    SierpinskiTriangle* m_triangle = nullptr;
};


#endif //TREE_FRACTALSCENE_H
