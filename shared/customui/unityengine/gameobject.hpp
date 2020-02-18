namespace CustomUI::UnityEngine {

    class GameObject : public Object {
        public:
            PROPERTY_GET(active, bool);
            PROPERTY_GET(gameObject, GameObject*);
            PROPERTY_GET_SET(layer, int);
            PROPERTY_GET_SET(tag, std::string);
            PROPERTY_GET(transform, Transform*);
            
            static GameObject* Find(std::string type);
            
            Component* AddComponent(Il2CppObject* type);
            Component* GetComponent(Il2CppObject* type);
            Component* GetComponentInChildren(Il2CppObject* type, bool includeInactive = false);
            Component* GetComponentInParent(Il2CppObject* type);
            Array<Component*>* GetComponents();
            Array<Component*>* GetComponents(Il2CppObject* type);
            Array<Component*>* GetComponentsInChildren(Il2CppObject* type, bool includeInactive = false);
            Array<Component*>* GetComponentsInParent(Il2CppObject* type, bool includeInactive = false);

            void SetActive(bool active);
            void SetActiveRecursively(bool active);
            
    };

}