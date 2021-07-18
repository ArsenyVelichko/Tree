#include <android_native_app_glue.h>

#include <Log.h>

#include "EventLoop.h"
#include "templates/ControllerTemplate.h"
#include "OpenGL/GLView.h"

void android_main(android_app* app) {
    log_info("Start");

    auto view = new GLView(app);
    auto controller = new ControllerTemplate<GLView>(view);

    controller->bindAction(APP_CMD_INIT_WINDOW, &GLView::init);
    controller->bindAction(APP_CMD_TERM_WINDOW, &GLView::term);

    EventLoop loop(app);
    loop.addView(view);
    loop.addController(controller);

    loop.run();
}