#include "FractalScene.h"
#include "../Painters/MonoPainter.h"
#include "Log.h"

void FractalScene::create(android_app* app, size_t width, size_t height) {
    m_width = width;
    m_height = height;

    double sideLen = width * 0.75;
    double y = height / 2.0 - sqrt(3.0) * sideLen / 6.0;
    double x1 = (width - sideLen) / 2.0;
    double x2 = x1 + sideLen;

    m_triangle = new SierpinskiTriangle(DoubleVec2(x1, y), DoubleVec2(x2, y));

    auto painter = new MonoPainter(app->activity->assetManager);
    painter->setColor(Color(0.9f, 0.1f, 0.1f, 1.0f));

    DoubleMat4 camera = glm::ortho(0.0, double(width), 0.0, double(height));
    painter->setTransform(camera);

    std::string painterName = "Mono";
    registerPainter(painter, painterName);
    addItem(m_triangle, painterName);
}

void FractalScene::touchEvent(AInputEvent* event) {
    if (AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN) {
        float x = AMotionEvent_getX(event, 0);
        log_debug("Touch event x coordinate: %f", x);

        float y = AMotionEvent_getY(event, 0);
        log_debug("Touch event y coordinate: %f", y);

        if (y < m_height / 2.0) {
            m_triangle->enlarge();
        } else {
            m_triangle->reduce();
        }
    }
}
