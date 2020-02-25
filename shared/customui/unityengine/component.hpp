namespace CustomUI::UnityEngine {

    class Transform;

    class Component : public Object {
        public:
            PROPERTY_GET(transform, Transform*);
            PROPERTY_GET_SET(tag, std::string);
            PROPERTY_GET(gameObject, GameObject*);

            inline Component* GetComponent(Il2CppObject* type){ return this->get_gameObject()->GetComponent(type); }
            inline Component* GetComponentInChildren(Il2CppObject* type, bool includeInactive = false){ return this->get_gameObject()->GetComponentInChildren(type, includeInactive); }
            inline Component* GetComponentInParent(Il2CppObject* type){ return this->get_gameObject()->GetComponentInParent(type); }
            inline Array<Component*>* GetComponents(Il2CppObject* type){ return this->get_gameObject()->GetComponents(type); }
            inline Array<Component*>* GetComponentsInChildren(Il2CppObject* type, bool includeInactive = false){ return this->get_gameObject()->GetComponentsInChildren(type, includeInactive); }
            inline Array<Component*>* GetComponentsInParent(Il2CppObject* type, bool includeInactive = false){ return this->get_gameObject()->GetComponentsInParent(type, includeInactive); }

    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::Component*, "UnityEngine", "Component");