#pragma once

#include <type_traits>
#include "il2cpp-utils-methods.hpp"

namespace bs_hook {
    template<class T>
    concept has_dispose_vt = requires (T t) {
        {t.Dispose();}
    };
    template<class T>
    concept has_dispose_rt = requires (T t) {
        {t->Dispose();}
    };
    template<class T>
    requires (!std::is_reference_v<T> && (has_dispose_vt<T> || has_dispose_rt<T> || std::is_convertible_v<T, Il2CppObject*>))
    struct Disposable {
        Disposable(T t) : value(t) {}
        Disposable(Disposable const&) = delete;
        explicit operator T() {return value;}
        operator T&() {return value;}
        T operator ->() {return value;}
        ~Disposable() {
            if constexpr (has_dispose_vt<T>) {
                value.Dispose();
            } else if constexpr (has_dispose_rt<T>) {
                value->Dispose();
            } else {
                if (!il2cpp_utils::RunMethod<Il2CppObject*, false>(value, "Dispose")) {
                    SAFE_ABORT();
                }
            }
        }
        private:
        T value;
    };
}