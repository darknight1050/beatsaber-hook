#include "../customui.hpp"

namespace CustomUI::UnityEngine {

    GameObject* GameObject::Find(std::string name){
        GameObject* gameObject;
        Il2CppObject* instance = nullptr;
        il2cpp_utils::RunMethod(&gameObject, instance, "Find", il2cpp_utils::createcsstr(name));
        return gameObject;
    }
}