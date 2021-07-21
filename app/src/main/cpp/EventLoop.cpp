#include "EventLoop.h"

#include "Log/Log.h"

EventLoop::EventLoop(android_app* app) : m_app(app) {
    app->userData = this;
    app->onAppCmd = onAppCmd;
    app->onInputEvent = onAppInput;
}

void EventLoop::run() {
    android_poll_source* source;

    while (true) {
        //Process events
        int events;
        while (ALooper_pollAll(-1, nullptr, &events, (void**)&source) >= 0) {

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

    for (auto cmdHandler : eventLoop->m_cmdHandlers) {
        cmdHandler->handleCmd(cmd);
    }
}

int32_t EventLoop::onAppInput(android_app* app, AInputEvent* event) {
    auto* eventLoop = static_cast<EventLoop*>(app->userData);

    bool isHandled = false;
    for (auto inputHandler : eventLoop->m_inputHandlers) {
        isHandled &= inputHandler->handleInput(event);
    }
    return isHandled;
}

void EventLoop::update() {
    for (auto view : m_views) {
        view->update();
    }
}

EventLoop::~EventLoop() {
    for (auto view : m_views) {
        delete view;
    }

    for (auto cmdHandler : m_cmdHandlers) {
        delete cmdHandler;
    }

    for (auto inputHandler : m_inputHandlers) {
        delete inputHandler;
    }
}