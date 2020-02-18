namespace CustomUI::UnityEngine {

    
    class Canvas : public Behaviour {
        public:
            enum RenderMode
            {
                ScreenSpaceOverlay,
                ScreenSpaceCamera,
                WorldSpace
            }; 
            PROPERTY_GET_SET(renderMode, RenderMode);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Canvas*, "UnityEngine", "Canvas");
DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Canvas::RenderMode, "System", "Int32");