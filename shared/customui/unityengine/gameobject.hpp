namespace CustomUI::UnityEngine {

    class GameObject : public Object {
        public:
            PROPERTY_GET(active, bool);
            PROPERTY_GET(gameObject, GameObject*);
            PROPERTY_GET_SET(layer, int);
            PROPERTY_GET_SET(tag, std::string);
            PROPERTY_GET(transform, Transform*);
            
            static GameObject* Find(std::string type);
            
            inline Component* AddComponent(Il2CppObject* type){ return MethodWrapper::RunSimpleMethod<Component*>(this, "AddComponent", type); }
            inline Component* GetComponent(Il2CppObject* type){ return MethodWrapper::RunSimpleMethod<Component*>(this, "GetComponent", type); }
            inline Component* GetComponentInChildren(Il2CppObject* type, bool includeInactive = false){ return MethodWrapper::RunSimpleMethod<Component*>(this, "GetComponentInChildren", type, includeInactive); }
            inline Component* GetComponentInParent(Il2CppObject* type){ return MethodWrapper::RunSimpleMethod<Component*>(this, "GetComponentInParent", type); }
            inline Array<Component*>* GetComponents(){ return MethodWrapper::RunSimpleMethod<Array<Component*>*>(this, "GetComponents"); }
            inline Array<Component*>* GetComponents(Il2CppObject* type){ return MethodWrapper::RunSimpleMethod<Array<Component*>*>(this, "GetComponents", type); }
            inline Array<Component*>* GetComponentsInChildren(Il2CppObject* type, bool includeInactive = false){ return MethodWrapper::RunSimpleMethod<Array<Component*>*>(this, "GetComponentsInChildren", type, includeInactive); }
            inline Array<Component*>* GetComponentsInParent(Il2CppObject* type, bool includeInactive = false){ return MethodWrapper::RunSimpleMethod<Array<Component*>*>(this, "GetComponentsInParent", type, includeInactive); }

            inline void SetActive(bool active){ MethodWrapper::RunSimpleMethod(this, "SetActive", active); }
            inline void SetActiveRecursively(bool active){ MethodWrapper::RunSimpleMethod(this, "SetActiveRecursively", active); }
    };

}

DEFINE_IL2CPP_ARG_TYPE(CustomUI::UnityEngine::GameObject*, "UnityEngine", "GameObject");