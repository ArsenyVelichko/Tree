#ifndef TREE_ICONTROLLER_H
#define TREE_ICONTROLLER_H

#include <stdint.h>
#include <memory>

class IController {
public:
    virtual ~IController() = default;

    virtual void processCmd(int32_t cmd) = 0;
};

#endif //TREE_ICONTROLLER_H
