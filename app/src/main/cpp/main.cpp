#include <android_native_app_glue.h>

#include <Log.h>

#include "EventLoop.h"
#include "Controllers/InputController.h"
#include "Controllers/CmdController.h"
#include "OpenGL/Scenes/FractalScene.h"
#include "OpenGL/GLView.h"

void android_main(android_app* app) {
    log_info("Start");

    auto view = new GLView(app);
    auto scene = new FractalScene;

    view->setScene(scene);

    auto viewController = new CmdController<GLView>(view);
    viewController->bindAction(APP_CMD_INIT_WINDOW, &GLView::init);
    viewController->bindAction(APP_CMD_TERM_WINDOW, &GLView::term);

    auto sceneController = new InputController<FractalScene>(scene);
    sceneController->bindAction(AINPUT_EVENT_TYPE_MOTION, &FractalScene::touchEvent);

    EventLoop loop(app);

    loop.addView(view);
    loop.addCmdHandler(viewController);
    loop.addInputHandler(sceneController);

    loop.run();
}