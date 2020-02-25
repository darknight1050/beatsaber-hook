namespace MethodWrapper {

    
    template<class... TArgs>
    void RunSimpleMethod(Il2CppObject* instance, std::string methodName, TArgs&& ...params){
        if(instance == nullptr){
            log(ERROR, "MethodWrapper: RunSimpleMethod: Null instance parameter! (%s)", methodName.c_str());
            return;
        }
        if(!il2cpp_utils::RunMethod(instance, methodName, params...)){
            log(ERROR, "MethodWrapper: RunSimpleMethod: failed! (%s)", methodName.c_str());
        }
    }

    template<class TOut, class... TArgs>
    TOut RunSimpleMethod(Il2CppObject* instance, std::string methodName, TArgs&& ...params) {
        TOut value;
        if(instance == nullptr){
            log(ERROR, "MethodWrapper: RunSimpleMethod: Null instance parameter! (%s)", methodName.c_str());
            return value;
        }
        if(!il2cpp_utils::RunMethod(&value, instance, methodName, params...)){
            log(ERROR, "MethodWrapper: RunSimpleMethod: Running %s failed!", methodName.c_str());
        }
        return value;
    }

    template<class TOut>
    TOut GetProperty(Il2CppObject* instance, std::string name) {
        return RunSimpleMethod<TOut>(instance, std::string("get_") + name);;
    }

    template<>
    std::string GetProperty<std::string>(Il2CppObject* instance, std::string name);

    template<class TOut>
    void SetProperty(Il2CppObject* instance, std::string name, TOut value) {
        RunSimpleMethod(instance, std::string("set_") + name, value);
    }

    template<>
    void SetProperty<std::string>(Il2CppObject* instance, std::string name, std::string value);
    
}

#define PROPERTY_GET(name, type) \
type get_ ## name() { return MethodWrapper::GetProperty<type>(this, #name); }

#define PROPERTY_SET(name, type) \
void set_ ## name(type value) { MethodWrapper::SetProperty<type>(this, #name, value); }

#define PROPERTY_GET_SET(name, type) PROPERTY_GET(name, type) PROPERTY_SET(name, type)
