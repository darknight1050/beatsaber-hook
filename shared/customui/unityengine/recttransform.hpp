namespace CustomUI::UnityEngine {

    class RectTransform : public Transform {
        public:
            enum Edge
            {
                Left,
                Right,
                Top,
                Bottom
            };

		    enum Axis
            {
                Horizontal,
                Vertical
            };

            PROPERTY_GET_SET(anchoredPosition, Vector2);
            PROPERTY_SET(anchoredPosition3D, Vector3);
            PROPERTY_GET_SET(anchorMax, Vector2);
            PROPERTY_GET_SET(anchorMin, Vector2);
            PROPERTY_GET_SET(offsetMax, Vector2);
            PROPERTY_SET(offsetMin, Vector2);
            PROPERTY_GET_SET(pivot, Vector2);
            PROPERTY_GET(rect, Rect);
            PROPERTY_GET_SET(sizeDelta, Vector2);

            inline Vector3 get_anchoredPosition3D(){
                Vector2 anchoredPosition = get_anchoredPosition();
                return Vector3(anchoredPosition.x, anchoredPosition.y, get_localPosition().z);
            }

            inline Vector2 get_offsetMin(){
                Vector2 sizeDelta = get_sizeDelta();
                Vector2 pivot = get_pivot();
                return get_anchoredPosition() - Vector2(sizeDelta.x * pivot.x, sizeDelta.y * pivot.y);
            }

            inline void SetSize(Vector2 newSize){
                SetSizeWithCurrentAnchors(Axis::Horizontal, newSize.x);
                SetSizeWithCurrentAnchors(Axis::Vertical, newSize.y);
            }

            inline void ForceUpdateRectTransforms(){ return MethodWrapper::RunSimpleMethod(this, "ForceUpdateRectTransforms"); }
            inline void SetSizeWithCurrentAnchors(Axis axis, float size){ return MethodWrapper::RunSimpleMethod(this, "SetSizeWithCurrentAnchors", axis, size); }
            inline void SetInsetAndSizeFromParentEdge(Edge edge, float inset, float size){ return MethodWrapper::RunSimpleMethod(this, "SetInsetAndSizeFromParentEdge", edge, inset, size); }
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::RectTransform*, "UnityEngine", "RectTransform");
DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::RectTransform::Edge, "System", "Int32");
DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::RectTransform::Axis, "System", "Int32");