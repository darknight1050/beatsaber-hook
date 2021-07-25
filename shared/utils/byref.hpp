#pragma once
#include "il2cpp-type-check.hpp"

/// @brief Represents a byref parameter.
/// This is REQUIRED for codegen invokes, as RunMethodThrow can't tell the difference between a reference parameter and a byref on constexpr time.
/// This wraps a reference and the sizeof it must be the size of a pointer.
template<class T>
struct ByRef {
    ByRef(T& val) : heldRef(val) {}

    T& heldRef;
    static_assert(sizeof(T*) == sizeof(void*));
};

// Type specializations for byref specifics

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ByRef<T>> {
    static inline Il2CppClass* get() {
        return ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<T&>::get();
    }
};

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ByRef<T>&> {
    static inline Il2CppClass* get() {
        return ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ByRef<T>>::get();
    }
};

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ByRef<T>&&> {
    static inline Il2CppClass* get() {
        return ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<ByRef<T>>::get();
    }
};

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_arg_type<ByRef<T>> {
    static inline const Il2CppType* get(ByRef<T> arg) {
        Il2CppClass* klass = ::il2cpp_utils::il2cpp_type_check::il2cpp_arg_class<T&>::get(arg.heldRef);
        return &klass->this_arg;
    }
};

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_arg_type<ByRef<T>&> {
    static inline const Il2CppType* get(ByRef<T>& arg) {
        Il2CppClass* klass = ::il2cpp_utils::il2cpp_type_check::il2cpp_arg_class<T&>::get(arg.heldRef);
        return &klass->this_arg;
    }
};

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_arg_type<ByRef<T>&&> {
    static inline const Il2CppType* get(ByRef<T>&& arg) {
        Il2CppClass* klass = ::il2cpp_utils::il2cpp_type_check::il2cpp_arg_class<T&>::get(arg.heldRef);
        return &klass->this_arg;
    }
};

// Creates a ByRef type to wrap a reference
#define byref(...) (ByRef(__VA_ARGS__))