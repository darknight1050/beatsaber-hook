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
            PROPERTY_GET_SET(material, Material*);
            PROPERTY_GET_SET(sprite, Sprite*);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::Image*, "UnityEngine.UI", "Image");
DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::Image::Type, "System", "Int32");
DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::UI::Image::FillMethod, "System", "Int32");