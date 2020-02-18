namespace CustomUI::UnityEngine::UI {

    class CanvasScaler : public EventSystems::UIBehaviour {
        public:
            PROPERTY_GET_SET(scaleFactor, float);
            PROPERTY_GET_SET(dynamicPixelsPerUnit, float);
            PROPERTY_GET_SET(referencePixelsPerUnit, float);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::CanvasScaler*, "UnityEngine.UI", "CanvasScaler");