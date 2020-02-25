#include "customui.hpp"

namespace MethodWrapper {

    template<>
    std::string GetProperty<std::string>(Il2CppObject* instance, std::string name) {
        Il2CppString* value = GetProperty<Il2CppString*>(instance, name);
        return to_utf8(csstrtostr(value));
    }
    
    template<>
    void SetProperty<std::string>(Il2CppObject* instance, std::string name, std::string value) {
        SetProperty(instance, name, il2cpp_utils::createcsstr(value));
    }
    
}