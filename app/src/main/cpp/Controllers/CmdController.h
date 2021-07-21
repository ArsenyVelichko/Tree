#ifndef TREE_CMDCONTROLLER_H
#define TREE_CMDCONTROLLER_H

#include "Controller.h"
#include "../ICmdHandler.h"

template<class PawnType, class Base = Controller<PawnType, int32_t>>
class CmdController : public Base, public ICmdHandler {
public:
    CmdController(PawnType* pawn) : Base(pawn) {}

protected:
    void handleCmd(int32_t cmd) override {
        Base::handle(cmd);
    }
};

#endif //TREE_CMDCONTROLLER_H
