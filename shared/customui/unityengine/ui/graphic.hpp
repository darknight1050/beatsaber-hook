namespace CustomUI::UnityEngine::UI {

    class Graphic : public EventSystems::UIBehaviour {
        public:
            PROPERTY_GET(canvas, Canvas*);
            PROPERTY_GET_SET(color, Color);
            PROPERTY_GET_SET(rectTransform, RectTransform*);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::Graphic*, "UnityEngine.UI", "Graphic");