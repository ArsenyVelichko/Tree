#ifndef TREE_IVIEW_H
#define TREE_IVIEW_H

#include <memory>

class IView {
public:
    virtual ~IView() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void term() = 0;
};

#endif //TREE_IVIEW_H
