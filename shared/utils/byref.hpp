#pragma once
#include "il2cpp-type-check.hpp"

/// @brief Represents a byref parameter.
/// This is REQUIRED for codegen invokes, as RunMethodThrow can't tell the difference between a reference parameter and a byref on constexpr time.
/// This wraps a reference and the sizeof it must be the size of a pointer.
template<class T>
requires (!std::is_reference_v<T>)
struct ByRef {
    ByRef(T& val) : heldRef(val) {}

    T& heldRef;
    static_assert(sizeof(T*) == sizeof(void*));
};

// Type specializations for byref specifics
// We do not need il2cpp_no_arg_class specialization for ByRef, since it will never get to that point.

template<typename T>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_type<ByRef<T>> {
    static inline const Il2CppType* get() {
        static auto* typ = &::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<T>::get()->this_arg;
        return typ;
    }
};

// Creates a ByRef type to wrap a reference
#define byref(...) (ByRef(__VA_ARGS__))