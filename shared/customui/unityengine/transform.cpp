#include "../customui.hpp"

namespace CustomUI::UnityEngine {
    
    Transform* Transform::GetParent(){
        Transform* parent;
        il2cpp_utils::RunMethod(&parent, this, "GetParent");
        return parent;
    }

    void Transform::SetParent(Transform* parent){
        il2cpp_utils::RunMethod(this, "SetParent", parent);
    }

    void Transform::SetParent(Transform* parent, bool worldPositionStays){
        il2cpp_utils::RunMethod(this, "SetParent", parent, worldPositionStays);
    }
}