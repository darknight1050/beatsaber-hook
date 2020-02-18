namespace CustomUI::UnityEngine::UI {

    class Button : public Selectable {
        public:
            typedef void OnClickFunction(Button* button);
            void AddOnClick(OnClickFunction* onClick);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::Button*, "UnityEngine.UI", "Button");