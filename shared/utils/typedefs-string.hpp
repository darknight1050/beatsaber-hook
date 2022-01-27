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
    std::size_t convstr(char16_t const* inp, char* outp, int isz, int osz);

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
        std::string val(sz * 2, '\0');
        auto resSize = il2cpp_utils::detail::convstr(chars, val.data(), sz, val.size());
        val.resize(resSize);
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
    constexpr StringW(ConstString<sz>& conststring) noexcept : inst(static_cast<Il2CppString*>(conststring)) {}
    constexpr StringW(std::nullptr_t npt) noexcept : inst(npt) {}
    constexpr StringW() noexcept : inst(nullptr) {}

    constexpr void const* convert() const noexcept {
        return inst;
    }
    constexpr void* convert() noexcept {
        return inst;
    }
    constexpr operator Il2CppString const*() const noexcept {
        return inst;
    }
    constexpr operator Il2CppString*() noexcept {
        return inst;
    }
    constexpr Il2CppString const* operator->() const {
        return inst;
    }
    constexpr Il2CppString* operator->() noexcept {
        return inst;
    }
    constexpr operator bool() const {
        return inst != nullptr; 
    }
    constexpr bool operator ==(std::nullptr_t rhs) const noexcept {
        return inst == rhs;
    }

    template<int sz>
    constexpr bool operator <(ConstString<sz> const& rhs) const {
        if (!inst) return true;

        Il2CppChar* first = inst->chars; 
        Il2CppChar* second = rhs->chars; 
        Il2CppChar* firstEnd = first + inst->length; 
        Il2CppChar* secondEnd = second + rhs->length - 1; 

        while (first != firstEnd && second != secondEnd)
        {
            if (*first == *second)
            {
                first++; second++;
                continue;
            }
            return *first < *second;
        }
        // if we got here, and second is not second end, we had a shorter first, so it should be true
        // if second is the end, we are longer, so it should be false
        return second != secondEnd;
    }

    bool operator <(StringW const& rhs) const;
    bool operator <(const std::string_view rhs) const;
    bool operator <(const std::u16string_view rhs) const;

    template<int sz>
    constexpr bool operator ==(ConstString<sz> const& rhs) const {
        Il2CppChar* first = inst->chars; 
        Il2CppChar* second = rhs.inst->chars; 
        Il2CppChar* firstEnd = first + inst->length; 
        Il2CppChar* secondEnd = second + rhs.inst->length; 

        while (first != firstEnd && second != secondEnd)
        {
            if (*first != *second) return false;
            first++; second++;
        }

        return first == firstEnd && second == secondEnd;
    }

    bool operator ==(StringW const& rhs) const;
    bool operator ==(const std::string_view rhs) const;
    bool operator ==(const std::u16string_view rhs) const;

    
    operator std::string() const;
    operator std::u16string() const;
    operator std::wstring() const;
    operator std::u16string_view();
    operator const std::u16string_view() const;

    private:
    Il2CppString* inst;
};
static_assert(sizeof(StringW) == sizeof(void*));
DEFINE_IL2CPP_DEFAULT_TYPE(StringW, string);
NEED_NO_BOX(StringW);
