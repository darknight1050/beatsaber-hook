namespace CustomUI::UnityEngine {

    
    class Material : public Object {
        public:
            PROPERTY_GET_SET(color, Color);
    };
    
}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Material*, "UnityEngine", "Material");

