#ifndef TREE_CONTROLLER_H
#define TREE_CONTROLLER_H

#include <map>

#include "../ICmdHandler.h"

template<class PawnType, class HandleType, class... Args>
class Controller {
public:
    explicit Controller(PawnType* pawn);

    using PawnAction = void (PawnType::*) (Args...);
    void bindAction(HandleType key, PawnAction action);

    bool handle(HandleType key, Args... args);

private:
    PawnType* m_pawn;
    std::map<int32_t, PawnAction> m_bindingMap;
};

#include "Controller.tpp"

#endif //TREE_CONTROLLER_H
