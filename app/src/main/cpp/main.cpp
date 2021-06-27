#include <android_native_app_glue.h>

#include "Log/Log.h"
#include "EventLoop.h"
#include "Tree/TreeController.h"

void android_main(android_app* app) {
    auto tree = new Tree;
    auto view = new TreeView(app);
    auto controller = new TreeController(tree, view);

    EventLoop loop(app);
    loop.addController(controller);
    loop.addView(view);
    loop.run();

    delete controller;
    delete tree;
    delete view;
}