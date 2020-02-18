namespace CustomUI::UnityEngine {

    class Transform : public Component {
        public:
            PROPERTY_GET_SET(position, Vector3);
            PROPERTY_GET_SET(localPosition, Vector3);
            PROPERTY_GET_SET(localScale, Vector3);
            PROPERTY_GET_SET(eulerAngles, Vector3);
            PROPERTY_GET_SET(localEulerAngles, Vector3);

            Transform* GetParent();
            void SetParent(Transform* parent);
            void SetParent(Transform* parent, bool worldPositionStays);
    };

}