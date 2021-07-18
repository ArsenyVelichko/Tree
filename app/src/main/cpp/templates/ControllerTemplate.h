#ifndef TREE_CONTROLLERTEMPLATE_H
#define TREE_CONTROLLERTEMPLATE_H

#include <map>

#include "../IController.h"

template<class T>
class ControllerTemplate : public IController {
public:
    explicit ControllerTemplate(T* pawn);

    using PawnAction = void (T::*) ();
    void bindAction(int32_t cmd, PawnAction action);

    void processCmd(int32_t cmd) override;

private:
    T* m_pawn;
    std::map<int32_t, PawnAction> m_bindingMap;
};

#include "ControllerTemplate.tpp"

#endif //TREE_CONTROLLERTEMPLATE_H
