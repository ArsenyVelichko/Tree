#ifndef TREE_TREECONTROLLER_H
#define TREE_TREECONTROLLER_H

#include <IController.h>

#include "TreeView.h"
#include "Tree.h"

class TreeController : public IController {
public:
    TreeController(Tree* tree, TreeView* view);

    void processCmd(int32_t cmd) override;

private:
    Tree* m_tree;
    TreeView* m_view;
};

#endif //TREE_TREECONTROLLER_H
