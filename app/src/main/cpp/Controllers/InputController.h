#ifndef TREE_INPUTCONTROLLER_H
#define TREE_INPUTCONTROLLER_H

#include "Controller.h"
#include "../IInputHandler.h"

template<class PawnType, class Base = Controller<PawnType, int32_t, AInputEvent*>>
class InputController : public Base, public IInputHandler {
public:
    InputController(PawnType* pawn) : Base(pawn) {}

protected:
    bool handleInput(AInputEvent* event) override {
        int32_t type = AInputEvent_getType(event);
        return Base::handle(type, event);
    }
};

#endif //TREE_INPUTCONTROLLER_H
