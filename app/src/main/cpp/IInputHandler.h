#ifndef TREE_IINPUTHANDLER_H
#define TREE_IINPUTHANDLER_H

#include <android_native_app_glue.h>

class IInputHandler {
public:
    virtual ~IInputHandler() = default;
    virtual bool handleInput(AInputEvent* event) = 0;
};

#endif //TREE_IINPUTHANDLER_H
