#ifndef TREE_ICMDHANDLER_H
#define TREE_ICMDHANDLER_H

#include <stdint.h>
#include <memory>

class ICmdHandler {
public:
    virtual ~ICmdHandler() = default;
    virtual void handleCmd(int32_t cmd) = 0;
};

#endif //TREE_ICMDHANDLER_H
