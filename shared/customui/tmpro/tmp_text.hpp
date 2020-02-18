namespace CustomUI::TMPro {

    class TMP_Text : public UnityEngine::UI::MaskableGraphic {
        public:
            PROPERTY_GET_SET(text, std::string);
            PROPERTY_GET_SET(color, Color);
            PROPERTY_GET_SET(fontSize, float);
            PROPERTY_GET_SET(font, TMP_FontAsset*);
            PROPERTY_GET(rectTransform, UnityEngine::RectTransform*);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::TMPro::TMP_Text*, "TMPro", "TMP_Text");