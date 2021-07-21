#include "FractalScene.h"
#include "../Painters/MonoPainter.h"
#include "Log.h"

void FractalScene::create(android_app* app) {
    m_triangle = new SierpinskiTriangle(DoubleVec2(-0.5, 0), DoubleVec2(0.5, 0));

    auto painter = new MonoPainter(app->activity->assetManager);

    std::string painterName = "Mono";
    registerPainter(painter, painterName);
    addItem(m_triangle, painterName);
}

void FractalScene::touchEvent(AInputEvent* event) {
    if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN) {
        float x = AMotionEvent_getX(event, 0);
        log_debug("x coordinate: %f", x);

        float y = AMotionEvent_getY(event, 0);
        log_debug("y coordinate: %f", y);

        m_triangle->enlarge();
    }
}
