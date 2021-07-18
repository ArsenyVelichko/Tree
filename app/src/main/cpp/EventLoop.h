#ifndef TREE_EVENTLOOP_H
#define TREE_EVENTLOOP_H

#include <android_native_app_glue.h>

#include <vector>

#include "IView.h"
#include "IController.h"

class EventLoop {
public:
    explicit EventLoop(android_app* app);
    ~EventLoop();

    void addController(IController* controller);
    void addView(IView* view);

    void run();
    void update();

    static void onAppCmd(android_app* app, int32_t cmd);

private:
    android_app* m_app;
    std::vector<IController*> m_controllers;
    std::vector<IView*> m_views;
};

inline void EventLoop::addController(IController* controller) {
    m_controllers.push_back(controller);
}

inline void EventLoop::addView(IView* view) {
    m_views.push_back(view);
}


#endif //TREE_EVENTLOOP_H
