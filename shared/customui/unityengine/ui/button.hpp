namespace CustomUI::UnityEngine::UI {

    class Button : public Selectable {
        public:
            void SetButtonText(std::string text);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::Button*, "UnityEngine.UI", "Button");