namespace CustomUI::UnityEngine {

    class Transform;
    
    class Object : public Il2CppObject {
        public:
            PROPERTY_GET_SET(name, std::string);
            static void DontDestroyOnLoad(Object* target);
            static void Destroy(Object* obj);
            static Object* Instantiate(Object* original);
            static Object* Instantiate(Object* original, Transform* parent);
            static Object* Instantiate(Object* original, Transform* parent, bool worldPositionStays);
    };
    
}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Object*, "UnityEngine", "Object");

