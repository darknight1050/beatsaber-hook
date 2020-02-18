namespace CustomUI::UnityEngine::UI {

    class Image : public MaskableGraphic {
        public:
            enum Type
            {
                Simple,
                Sliced,
                Tiled,
                Filled
            };

            enum FillMethod
            {
                Horizontal,
                Vertical,
                Radial90,
                Radial180,
                Radial360
            };
            PROPERTY_GET_SET(fillMethod, FillMethod);
            PROPERTY_GET_SET(type, Type);
            PROPERTY_GET_SET(sprite, Sprite*);
    };

}