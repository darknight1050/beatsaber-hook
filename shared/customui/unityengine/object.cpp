#include "../customui.hpp"

namespace CustomUI::UnityEngine {

    void Object::DontDestroyOnLoad(Object* target){
        il2cpp_utils::RunMethod(nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "DontDestroyOnLoad", 1), target);
    }

    void Object::Destroy(Object* obj){
        il2cpp_utils::RunMethod(nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "Destroy", 1), obj);
    }

    Object* Object::Instantiate(Object* original){
        Object* object;
        il2cpp_utils::RunMethod(&object, nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "Instantiate", 1), original);
        return object;
    }

    Object* Object::Instantiate(Object* original, Transform* parent){
        return Instantiate(original, parent, false);
    }

    Object* Object::Instantiate(Object* original, Transform* parent, bool worldPositionStays){
        Object* object;
        il2cpp_utils::RunMethod(&object, nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "Instantiate", 3), original, parent, worldPositionStays);
        return object;
    }
    
}