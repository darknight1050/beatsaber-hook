#include "customui.hpp"

namespace MethodWrapper {

    template<>
    std::string GetProperty<std::string>(Il2CppObject* instance, std::string name) {
        std::string methodName = std::string("get_") + name;
        Il2CppString* value;
        il2cpp_utils::RunMethod(&value, instance, methodName);
        return to_utf8(csstrtostr(value));
    }
    
    template<>
    void SetProperty<std::string>(Il2CppObject* instance, std::string name, std::string value) {
        std::string methodName = std::string("set_") + name;
        il2cpp_utils::RunMethod(instance, methodName, il2cpp_utils::createcsstr(value));
    }
    
}