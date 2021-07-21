#ifndef TREE_EVENTLOOP_H
#define TREE_EVENTLOOP_H

#include <android_native_app_glue.h>

#include <vector>

#include "IView.h"
#include "ICmdHandler.h"
#include "IInputHandler.h"

class EventLoop {
public:
    explicit EventLoop(android_app* app);
    ~EventLoop();

    void addCmdHandler(ICmdHandler* cmdHandler);
    void addInputHandler(IInputHandler* inputHandler);
    void addView(IView* view);

    void run();
    void update();

    static void onAppCmd(android_app* app, int32_t cmd);
    static int32_t onAppInput(android_app* app, AInputEvent* event);

private:
    android_app* m_app;
    std::vector<ICmdHandler*> m_cmdHandlers;
    std::vector<IInputHandler*> m_inputHandlers;
    std::vector<IView*> m_views;
};

inline void EventLoop::addCmdHandler(ICmdHandler* cmdHandler) {
    m_cmdHandlers.push_back(cmdHandler);
}

inline void EventLoop::addInputHandler(IInputHandler* inputHandler) {
    m_inputHandlers.push_back(inputHandler);
}

inline void EventLoop::addView(IView* view) {
    m_views.push_back(view);
}


#endif //TREE_EVENTLOOP_H
