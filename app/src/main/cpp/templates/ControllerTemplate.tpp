template <class T>
ControllerTemplate<T>::ControllerTemplate(T* pawn) : m_pawn(pawn) {}

template <class T>
void ControllerTemplate<T>::bindAction(int32_t cmd, PawnAction action) {
    m_bindingMap[cmd] = action;
}

template<class T>
void ControllerTemplate<T>::processCmd(int32_t cmd) {
    if (m_bindingMap.find(cmd) != m_bindingMap.end()) {
        (m_pawn->*m_bindingMap[cmd])();
    }
}