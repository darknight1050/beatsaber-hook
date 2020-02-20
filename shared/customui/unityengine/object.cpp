#include "../customui.hpp"

namespace CustomUI::UnityEngine {

    void Object::DontDestroyOnLoad(Object* target){
        il2cpp_utils::RunMethod(nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "DontDestroyOnLoad", 1), target);
    }

    Object* Object::Instantiate(Object* original){
        Object* object;
        il2cpp_utils::RunMethod(&object, nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "Instantiate", 1), original);
        return object;
    }
    
}