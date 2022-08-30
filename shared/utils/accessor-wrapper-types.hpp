#pragma once
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <string>
#include <array>
#include <algorithm>

#include "il2cpp-utils-properties.hpp"
#include "il2cpp-utils-fields.hpp"
#include "typedefs-object.hpp"

namespace bs_hook {
    namespace internal {
        template<std::size_t sz>
        struct NTTPString {
            constexpr NTTPString(char const(&n)[sz]) : data{} {
                std::copy_n(n, sz, data.begin());
            }
            std::array<char, sz> data;
        };
    }

    struct PropertyException : public il2cpp_utils::exceptions::StackTraceException {
        using StackTraceException::StackTraceException;
    };

    struct NullException : public il2cpp_utils::exceptions::StackTraceException {
        using StackTraceException::StackTraceException;
    };

    struct FieldException : public il2cpp_utils::exceptions::StackTraceException {
        using StackTraceException::StackTraceException;
    };
    // TODO: Note that these types are not safe to be passed into RunMethod by themselves (or generic functions)
    // This is because they are wrapper over T, as opposed to being analogous to T.
    // We cannot EASILY solve this using wrapper types, because we could be holding a value type as T.
    // This makes things tricky and we should come back to this when we are confident we can handle this case correctly.


    template<internal::NTTPString name, class T, bool get, bool set>
    /// @brief Represents a InstanceProperty on a wrapper type. Forwards to calling the get/set methods where applicable.
    struct InstanceProperty;
    
    template<internal::NTTPString name, class T>
    struct InstanceProperty<name, T, true, false> {
        explicit InstanceProperty(void* inst) noexcept : instance(inst) {}
        operator T() const {
            auto res = il2cpp_utils::GetPropertyValue<T, false>(reinterpret_cast<Il2CppObject*>(const_cast<void*>(instance)), name.data.data());
            if (!res) throw PropertyException(std::string("Failed to get instance property: ") + name.data.data());
            return *res;
        }
        private:
        void* instance;
    };

    template<internal::NTTPString name, class T>
    struct InstanceProperty<name, T, false, true> {
        explicit InstanceProperty(void* inst) noexcept : instance(inst) {}
        InstanceProperty& operator=(T&& t) {
            auto val = reinterpret_cast<Il2CppObject*>(instance);
            auto res = il2cpp_utils::SetPropertyValue<false>(val, name.data.data(), std::forward<decltype(t)>(t));
            if (!res) throw PropertyException(std::string("Failed to set instance property: ") + name.data.data());
            return *this;
        }
        private:
        void* instance;
    };

    template<internal::NTTPString name, class T>
    struct InstanceProperty<name, T, true, true> {
        explicit InstanceProperty(void* inst) noexcept : instance(inst) {}
        operator T() const {
            auto res = il2cpp_utils::GetPropertyValue<T, false>(reinterpret_cast<Il2CppObject*>(const_cast<void*>(instance)), name.data.data());
            if (!res) throw PropertyException(std::string("Failed to get instance property: ") + name.data.data());
            return *res;
        }
        InstanceProperty& operator=(T&& t) {
            auto val = reinterpret_cast<Il2CppObject*>(instance);
            auto res = il2cpp_utils::SetPropertyValue<false>(val, name.data.data(), std::forward<decltype(t)>(t));
            if (!res) throw PropertyException(std::string("Failed to set instance property: ") + name.data.data());
            return *this;
        }
        private:
        void* instance;
    };

    template<class T, internal::NTTPString name, bool get, bool set>
    struct StaticProperty;

    template<class T, internal::NTTPString name>
    struct StaticProperty<T, name, true, false> {
        explicit StaticProperty(Il2CppClass* (*k)()) : klass_resolver(k) {}
        operator T() const {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static property with name: ") + name.data.data() + " is null!");
            auto res = il2cpp_utils::GetPropertyValue<T, false>(klass, name.data.data());
            if (!res) throw PropertyException(std::string("Failed to get static property: ") + name.data.data());
            return *res;
        }
        private:
        Il2CppClass* (*klass_resolver)();
    };

    template<class T, internal::NTTPString name>
    struct StaticProperty<T, name, false, true> {
        explicit StaticProperty(Il2CppClass* (*k)()) : klass_resolver(k) {}
        StaticProperty& operator=(T&& value) {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static property with name: ") + name.data.data() + " is null!");
            auto res = il2cpp_utils::SetPropertyValue<false>(klass, name.data.data(), std::forward<decltype(value)>(value));
            if (!res) throw PropertyException(std::string("Failed to set static property: ") + name.data.data());
            return *this;
        }
        private:
        Il2CppClass* (*klass_resolver)();
    };

    template<class T, internal::NTTPString name>
    struct StaticProperty<T, name, true, true> {
        explicit StaticProperty(Il2CppClass* (*k)()) : klass_resolver(k) {}
        operator T() const {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static property with name: ") + name.data.data() + " is null!");
            auto res = il2cpp_utils::GetPropertyValue<T, false>(klass, name.data.data());
            if (!res) throw PropertyException(std::string("Failed to get static property: ") + name.data.data());
            return *res;
        }
        StaticProperty& operator=(T&& value) {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static property with name: ") + name.data.data() + " is null!");
            auto res = il2cpp_utils::SetPropertyValue<false>(klass, name.data.data(), std::forward<decltype(value)>(value));
            if (!res) throw PropertyException(std::string("Failed to set static property: ") + name.data.data());
            return *this;
        }
        private:
        Il2CppClass* (*klass_resolver)();
    };

    template<class T, std::size_t offset, bool assignable>
    struct InstanceField;
    
    template<class T, std::size_t offset>
    struct InstanceField<T, offset, true> {
        explicit InstanceField(void* inst) noexcept : instance(inst) {}
        operator T() const {
            if (instance == nullptr) throw NullException("Instance field access failed at offset: " + std::to_string(offset) + " because instance was null!");
            // No wbarrier required for unilateral gets
            if constexpr (il2cpp_utils::has_il2cpp_conversion<T>) {
                // Handle wrapper types differently
                return T(*reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(const_cast<void*>(instance)) + offset));
            }
            return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(const_cast<void*>(instance)) + offset);
        }
        InstanceField& operator=(T&& t) {
            if (instance == nullptr) throw NullException("Instance field assignment failed at offset: " + std::to_string(offset) + " because instance was null!");
            
            if constexpr (il2cpp_utils::has_il2cpp_conversion<T>) {
                // We only do this if we are a wrapper type!
                il2cpp_functions::Init();
                // instance is actually unused for wbarrier, wbarrier call performs the assignment
                il2cpp_functions::gc_wbarrier_set_field(instance, reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(instance) + offset), t.convert());
            } else {
                // No wbarrier for types that are not wrapper types
                // Value types ALSO need a wbarrier, but for the whole size of themselves.
                // We need to xref trace to find the correct wbarrier set in this case, or call the set_field directly...
                // Which is a bit of a pain.
                *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(instance) + offset) = t;
            }
            return *this;
        }
        private:
        void* instance;
    };

    template<class T, std::size_t offset>
    struct InstanceField<T, offset, false> {
        explicit InstanceField(void* inst) noexcept : instance(inst) {}
        operator T() const {
            if (instance == nullptr) throw NullException("Instance field access failed at offset: " + std::to_string(offset) + " because instance was null!");
            // TODO: Also set wbarrier
            if constexpr (il2cpp_utils::has_il2cpp_conversion<T>) {
                // Handle wrapper types differently
                return T(*reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(const_cast<void*>(instance)) + offset));
            }
            return *reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(const_cast<void*>(instance)) + offset);
        }
        private:
        void* instance;
    };

    template<class T, internal::NTTPString name, bool assignable>
    struct StaticField;

    // Static fields all have proper wbarriers through using set field API calls

    template<class T, internal::NTTPString name>
    struct StaticField<T, name, false> {
        explicit StaticField(Il2CppClass* (*k)()) : klass_resolver(k) {}
        operator T() const {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static field with name: ") + name.data.data() + " is null!");
            auto val = il2cpp_utils::GetFieldValue<T>(klass, name.data.data());
            if (!val) throw FieldException(std::string("Could not get static field with name: ") + name.data.data());
            return *val;
        }
        private:
        Il2CppClass* (*klass_resolver)();
    };

    template<class T, internal::NTTPString name>
    struct StaticField<T, name, true> {
        explicit StaticField(Il2CppClass* (*k)()) : klass_resolver(k) {}
        operator T() const {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static field with name: ") + name.data.data() + " is null!");
            auto val = il2cpp_utils::GetFieldValue<T>(klass, name.data.data());
            if (!val) throw FieldException(std::string("Could not get static field with name: ") + name.data.data());
            return *val;
        }
        StaticField& operator=(T&& value) {
            auto klass = klass_resolver();
            if (!klass) throw NullException(std::string("Class for static field with name: ") + name.data.data() + " is null!");
            auto val = il2cpp_utils::SetFieldValue(klass, name.data.data(), std::forward<decltype(value)>(value));
            if (!val) throw FieldException(std::string("Could not set static field with name: ") + name.data.data());
            return *this;
        }
        private:
        Il2CppClass* (*klass_resolver)();
    };
}