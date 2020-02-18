namespace CustomUI::UnityEngine::UI {

    class Button : public Selectable {
        public:
            typedef void OnClickFunction(Button* button);
            void AddOnClick(OnClickFunction* onClick);
    };

}