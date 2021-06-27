#include "EventLoop.h"

#include "Log/Log.h"

EventLoop::EventLoop(android_app* app) : m_app(app) {
    app->userData = this;
    app->onAppCmd = onAppCmd;
}

void EventLoop::run() {
    android_poll_source* source;

    while (true) {
        //Process events
        int events, pollResult;
        while ((pollResult = ALooper_pollAll(-1, nullptr, &events, (void**)&source)) >= 0) {

            if (source != nullptr) {
                log_info("Event handled");
                source->process(m_app, source);
            }

            if (m_app->destroyRequested) {
                return;
            }

            update();
        }
    }
}

void EventLoop::onAppCmd(android_app* app, int32_t cmd) {
    auto* eventLoop = static_cast<EventLoop*>(app->userData);

    for (auto controller : eventLoop->m_controllers) {
        controller->processCmd(cmd);
    }
}

void EventLoop::addController(IController* controller) {
    m_controllers.push_back(controller);
}

void EventLoop::addView(IView* view) {
    m_views.push_back(view);
}

void EventLoop::update() {
    for (auto view : m_views) {
        view->update();
    }
}
