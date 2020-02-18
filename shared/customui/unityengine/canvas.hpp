namespace CustomUI::UnityEngine {

    enum RenderMode
    {
        ScreenSpaceOverlay,
        ScreenSpaceCamera,
        WorldSpace
    }; 

    class Canvas : public Behaviour {
        public:
            PROPERTY_GET_SET(renderMode, RenderMode);
    };

}