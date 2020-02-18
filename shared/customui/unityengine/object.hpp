namespace CustomUI::UnityEngine {

    
    class Object : public Il2CppObject {
        public:
            PROPERTY_GET_SET(name, std::string);
            static Object* Instantiate(Object* original);
    };
    
}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Object*, "UnityEngine", "Object");

