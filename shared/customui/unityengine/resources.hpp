namespace CustomUI::UnityEngine {

    namespace Resources {

        static inline Array<Object*>* FindObjectsOfTypeAll(Il2CppObject* type){
            Array<Object*>* objects;
            il2cpp_utils::RunMethod(&objects, il2cpp_utils::GetClassFromName("UnityEngine", "Resources"), "FindObjectsOfTypeAll", type);
            return objects;
        }

        static inline Array<Object*>* FindObjectsOfTypeAll(std::string_view nameSpace, std::string_view className){
            return FindObjectsOfTypeAll(il2cpp_utils::GetSystemType(nameSpace, className));
        }

        static inline Object* GetFirstObjectOfType(Il2CppObject* type){
            Array<Object*>* objects = FindObjectsOfTypeAll(type);
            if (objects != nullptr)
            {
                return objects->values[0];
            }
            else
            {
                return nullptr;
            }
        }

        static inline Object* GetFirstObjectOfType(std::string_view nameSpace, std::string_view className){
            return GetFirstObjectOfType(il2cpp_utils::GetSystemType(nameSpace, className));
        }

    };

}