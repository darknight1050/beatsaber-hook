#include "../customui.hpp"

namespace CustomUI::UnityEngine {

    GameObject* GameObject::Find(std::string name){
        GameObject* gameObject;
        Il2CppObject* instance = nullptr;
        il2cpp_utils::RunMethod(&gameObject, instance, "Find", il2cpp_utils::createcsstr(name));
        return gameObject;
    }

    Component* GameObject::AddComponent(Il2CppObject* type){
        Component* component;
        il2cpp_utils::RunMethod(&component, this, "AddComponent", type);
        return component;
    }
    
    Component* GameObject::GetComponent(Il2CppObject* type){
        Component* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponent", type);
        return component;
    }

    Component* GameObject::GetComponentInChildren(Il2CppObject* type, bool includeInactive){
        Component* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponentInChildren", type, includeInactive);
        return component;
    }

    Component* GameObject::GetComponentInParent(Il2CppObject* type){
        Component* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponentInParent", type);
        return component;
    }

    Array<Component*>* GameObject::GetComponents(){
        Array<Component*>* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponents");
        return component;
    }

    Array<Component*>* GameObject::GetComponents(Il2CppObject* type){
        Array<Component*>* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponents", type);
        return component;
    }

    Array<Component*>* GameObject::GetComponentsInChildren(Il2CppObject* type, bool includeInactive){
        Array<Component*>* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponentsInChildren", type, includeInactive);
        return component;
    }

    Array<Component*>* GameObject::GetComponentsInParent(Il2CppObject* type, bool includeInactive){
        Array<Component*>* component;
        il2cpp_utils::RunMethod(&component, this, "GetComponentsInParent", type, includeInactive);
        return component;
    }

    void GameObject::SetActive(bool active){
        il2cpp_utils::RunMethod(this, "SetActive", active);
    }

    void GameObject::SetActiveRecursively(bool active){
        il2cpp_utils::RunMethod(this, "SetActiveRecursively", active);
    }

}