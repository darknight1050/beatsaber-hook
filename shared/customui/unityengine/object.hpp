namespace CustomUI::UnityEngine {

    class Object : public Il2CppObject {
        public:
            PROPERTY_GET_SET(name, std::string);
            static Object* Instantiate(Object* original);
    };

}