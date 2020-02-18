namespace MethodWrapper {

    template<class T>
    T GetProperty(Il2CppObject* instance, std::string name) {
        std::string methodName = std::string("get_") + name;
        T value;
        il2cpp_utils::RunMethod(&value, instance, methodName);
        return value;
    }

    template<>
    std::string GetProperty<std::string>(Il2CppObject* instance, std::string name);

    template<class T>
    void SetProperty(Il2CppObject* instance, std::string name, T value) {
        std::string methodName = std::string("set_") + name;
        il2cpp_utils::RunMethod(instance, methodName, value);
    }

    template<>
    void SetProperty<std::string>(Il2CppObject* instance, std::string name, std::string value);
}

#define PROPERTY_GET(name, type) \
type get_ ## name() { return MethodWrapper::GetProperty<type>(this, #name); }

#define PROPERTY_SET(name, type) \
void set_ ## name(type value) { MethodWrapper::SetProperty<type>(this, #name, value); }

#define PROPERTY_GET_SET(name, type) PROPERTY_GET(name, type) PROPERTY_SET(name, type)
