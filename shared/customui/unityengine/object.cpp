#include "../customui.hpp"

namespace CustomUI::UnityEngine {

    Object* Object::Instantiate(Object* original){
        Object* object;
        il2cpp_utils::RunMethod(&object, nullptr, il2cpp_utils::FindMethod("UnityEngine", "Object", "Instantiate", 1), original);
        return object;
    }

}