namespace CustomUI::UnityEngine {

    class RectTransform : public Transform {
        public:
            PROPERTY_GET_SET(anchoredPosition, Vector2);
            PROPERTY_GET_SET(anchoredPosition3D, Vector3);
            PROPERTY_GET_SET(anchorMax, Vector2);
            PROPERTY_GET_SET(anchorMin, Vector2);
            PROPERTY_GET_SET(offsetMax, Vector2);
            PROPERTY_GET_SET(offsetMin, Vector2);
            PROPERTY_GET_SET(pivot, Vector2);
            PROPERTY_GET(rect, Rect);
            PROPERTY_GET_SET(sizeDelta, Vector2);
    };

}