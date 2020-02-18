namespace CustomUI::UnityEngine {

    class Behaviour : public Component {
        public:
            PROPERTY_GET_SET(enabled, bool);
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Behaviour*, "UnityEngine", "Behaviour");