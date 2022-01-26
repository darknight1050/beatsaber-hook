#pragma once

#include "utils-functions.h"
#include "il2cpp-type-check.hpp"
#include <string_view>
#include <string>
#include <stdexcept>
#include <locale>
#include <codecvt>

struct UseBeforeInitError : std::runtime_error {
    UseBeforeInitError(const char* v) : std::runtime_error(v) {}
};

struct Il2CppString;

namespace il2cpp_utils {
namespace detail {
    void convstr(char const* inp, char16_t* outp, int sz);
    void convstr(char16_t const* inp, char* outp, int sz);

    Il2CppString* alloc_str(std::string_view str);
    Il2CppString* alloc_str(std::u16string_view str);
}
}

// C# strings can only have 'int' max length.
template<int sz>
struct ConstString {
    // Manually allocated string, dtor destructs in place
    ConstString(const char (&st)[sz]) {
        if (il2cpp_functions::initialized) {
            klass = il2cpp_functions::defaults->string_class;
        }
        length = sz;
        il2cpp_utils::detail::convstr(st, chars, sz);
    }
    constexpr ConstString(const char16_t (&st)[sz]) noexcept {
        if (il2cpp_functions::initialized) {
            klass = il2cpp_functions::defaults->string_class;
        }
        length = sz;
        for (int i = 0; i < sz; i++) {
            chars[i] = st[i];
        }
        chars[sz] = '\0';
    }
    // Copies allowed? But should probably be avoided.
    ConstString(ConstString const&) = default;
    // Moves allowed
    ConstString(ConstString&&) = default;

    void init() noexcept {
        klass = il2cpp_functions::defaults->string_class;
    }

    constexpr operator Il2CppString*() {
        if (!klass) {
            if (il2cpp_functions::initialized) {
                klass = il2cpp_functions::defaults->string_class;
            } else {
                throw UseBeforeInitError("Il2CppClass* must be initialized before conversion! Call il2cpp_functions::Init before this conversion!");
            }
        }
        return reinterpret_cast<Il2CppString*>(&klass);
    }
    constexpr Il2CppString* operator->() noexcept {
        return operator Il2CppString*();
    }
    operator std::string() {
        std::string val;
        val.reserve(sz);
        il2cpp_utils::detail::convstr(chars, val.data(), sz);
        return val;
    }
    operator std::u16string() {
        return {chars, chars + length};
    }
    operator std::wstring() {
        return {chars, chars + length};
    }
    constexpr operator std::u16string_view() {
        return {chars, static_cast<std::size_t>(sz)};
    }

    private:
    void* klass = nullptr;
    void* monitor;
    int length;
    char16_t chars[sz + 1];
};

struct StringW {
    // Dynamically allocated string
    template<class T>
    requires (!std::is_convertible_v<T, Il2CppString*> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    StringW(T str) noexcept : inst(il2cpp_utils::detail::alloc_str(str)) {}
    constexpr StringW(void* ins) noexcept : inst(static_cast<Il2CppString*>(ins)) {}
    constexpr StringW(Il2CppString* ins) noexcept : inst(ins) {}
    template <int sz>
    constexpr StringW(ConstString<sz>& conststring) noexcept : inst(conststring) {}
    constexpr StringW(std::nullptr_t npt) noexcept : inst(npt) {}
    constexpr StringW() noexcept : inst(nullptr) {}

    operator std::string();
    constexpr void* convert() noexcept {
        return inst;
    }
    constexpr operator Il2CppString*() noexcept {
        return inst;
    }
    constexpr Il2CppString* operator->() noexcept {
        return inst;
    }
    operator std::u16string();
    operator std::wstring();
    operator std::u16string_view();

    private:
    Il2CppString* inst;
};
static_assert(sizeof(StringW) == sizeof(void*));
DEFINE_IL2CPP_DEFAULT_TYPE(StringW, string);
NEED_NO_BOX(StringW);
