namespace CustomUI::UnityEngine {

    class Transform : public Component {
        public:
            PROPERTY_GET_SET(position, Vector3);
            PROPERTY_GET_SET(localPosition, Vector3);
            PROPERTY_GET_SET(localScale, Vector3);
            PROPERTY_GET_SET(eulerAngles, Vector3);
            PROPERTY_GET_SET(localEulerAngles, Vector3);

            inline Transform* GetParent(){ return MethodWrapper::RunSimpleMethod<Transform*>(this, "GetParent"); }
            inline void SetParent(Transform* parent){ MethodWrapper::RunSimpleMethod(this, "SetParent", parent); }
            inline void SetParent(Transform* parent, bool worldPositionStays){ MethodWrapper::RunSimpleMethod(this, "SetParent", parent, worldPositionStays); }
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Transform*, "UnityEngine", "Transform");