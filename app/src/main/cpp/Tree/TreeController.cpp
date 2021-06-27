#include <EGLException.h>
#include <Log.h>
#include "TreeController.h"

TreeController::TreeController(Tree* tree, TreeView* view)
    : m_tree(tree), m_view(view) {}

void TreeController::processCmd(int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:

            try {
                m_view->init();
            } catch (EGLException& e) {
                log_error(e.what());
                m_view->term();
            }
            break;

        case APP_CMD_TERM_WINDOW:
            m_view->term();
            break;

        default:
            break;
    }
}
