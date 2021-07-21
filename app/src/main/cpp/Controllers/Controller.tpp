template<class PawnType, class HandleType, class... Args>
Controller<PawnType, HandleType, Args...>::Controller(PawnType* pawn) : m_pawn(pawn) {}

template<class PawnType, class HandleType, class... Args>
void Controller<PawnType, HandleType, Args...>::bindAction(HandleType key, PawnAction action) {
    m_bindingMap[key] = action;
}

template<class PawnType, class HandleType, class... Args>
bool Controller<PawnType, HandleType, Args...>::handle(HandleType key, Args... args) {
    if (m_bindingMap.find(key) != m_bindingMap.end()) {
        (m_pawn->*m_bindingMap[key])(args...);
        return true;
    }
    return false;
}