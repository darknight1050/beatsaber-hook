#pragma once

#include "utils-functions.h"
#include "il2cpp-type-check.hpp"
#include <string_view>
#include <string>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include "typedefs.h"

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
    
    template<typename T>
    requires(std::is_same_v<T, std::string_view> || std::is_same_v<T, std::u16string_view>)
    bool strcomp(Il2CppString const* lhs, T const rhs) noexcept
    {
        if (!lhs || lhs->length != (int)rhs.size()) return false;
    
        Il2CppChar const* first = lhs->chars; 
        auto const* second = rhs.data(); 
        Il2CppChar const* firstEnd = first + lhs->length; 
        auto const* secondEnd = second + (int)rhs.size(); 
    
        while (first != firstEnd && second != secondEnd)
        {
            if (*first != *second) return false;
            first++; second++;
        }
    
        return first == firstEnd && second == secondEnd;
    }

    template<typename T>
    requires(std::is_same_v<T, std::string_view> || std::is_same_v<T, std::u16string_view>)
    bool strless(Il2CppString const* lhs, T const rhs) noexcept {
        if (!lhs) return true;
    
        Il2CppChar const* first = lhs->chars; 
        auto const* second = rhs.data(); 
        Il2CppChar const* firstEnd = lhs->chars + lhs->length; 
        auto const* secondEnd = rhs.data() + rhs.size(); 
        
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
        
    Il2CppString* strappend(Il2CppString const* lhs, Il2CppString const* rhs) noexcept;
    Il2CppString* strappend(Il2CppString const* lhs, std::u16string_view const rhs) noexcept;
    Il2CppString* strappend(Il2CppString const* lhs, std::string_view const rhs) noexcept;
    
    template<typename T>
    requires(std::is_same_v<T, std::string_view> || std::is_same_v<T, std::u16string_view>)
    bool strstart(Il2CppString const* lhs, T const rhs) noexcept {
        if (!lhs || lhs->length < (decltype(lhs->length))rhs.size()) return false;
    
        Il2CppChar const* first = lhs->chars; 
        auto const* second = rhs.data(); 
        auto const* secondEnd = second + rhs.size(); 
        
        while (second != secondEnd)
        {
            if (*first == *second)
            {
                first++; second++;
                continue;
            }
            // we got a mismatch! return false;
            return false;
        }
        // if we got through the entire string it was all equal, return true
        return true;
    }
    
    template<typename T>
    requires(std::is_same_v<T, std::string_view> || std::is_same_v<T, std::u16string_view>)
    bool strend(Il2CppString const* lhs, T const rhs) noexcept {
        if (!lhs || lhs->length < (decltype(lhs->length))rhs.size()) return false;
    
        Il2CppChar const* first = lhs->chars + lhs->length - 1;
        auto const* secondBegin = rhs.data() - 1; 
        auto const* second = secondBegin + rhs.size(); 
        
        while (second != secondBegin)
        {
            if (*first == *second)
            {
                first--; second--;
                continue;
            }
            // we got a mismatch! return false;
            return false;
        }
        // if we got through the entire string it was all equal, return true
        return true;
    }
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

    friend struct StringW;
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
    constexpr Il2CppString const* operator->() const noexcept {
        return inst;
    }
    constexpr Il2CppString* operator->() noexcept {
        return inst;
    }
    constexpr operator bool() const noexcept {
        return inst != nullptr; 
    }

    constexpr bool operator ==(std::nullptr_t rhs) const noexcept {
        return inst == rhs;
    }

    template<typename T>
    requires (!std::is_convertible_v<T, Il2CppString*> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    StringW& operator +=(T const rhs) noexcept {
        if constexpr (std::is_constructible_v<std::u16string_view, T> && !std::is_same_v<T, std::u16string_view>)
            inst = StringW(il2cpp_utils::detail::strappend(inst, std::u16string_view(rhs)));
        else if constexpr (std::is_constructible_v<std::string_view, T> && !std::is_same_v<T, std::string_view>)
            inst = StringW(il2cpp_utils::detail::strappend(inst, std::string_view(rhs)));
        else inst = StringW(il2cpp_utils::detail::strappend(inst, rhs));
        return *this;
    }

    StringW& operator +=(StringW const& rhs) noexcept {
        inst = il2cpp_utils::detail::strappend(inst, rhs.inst);
        return *this;
    }

    StringW operator +(StringW const& rhs) const noexcept {
        return this->operator std::u16string().append(rhs);
    }
    template<typename T>
    requires (!std::is_convertible_v<T, Il2CppString*> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    StringW operator +(T const rhs) const noexcept {
        if constexpr (std::is_constructible_v<std::u16string_view, T> && !std::is_same_v<T, std::u16string_view>)
            return il2cpp_utils::detail::strappend(inst, std::u16string_view(rhs));
        else if constexpr (std::is_constructible_v<std::string_view, T> && !std::is_same_v<T, std::string_view>)
            return il2cpp_utils::detail::strappend(inst, std::string_view(rhs));
        else return il2cpp_utils::detail::strappend(inst, rhs);
    }

    bool operator <(StringW const& rhs) const noexcept;
    template<typename T>
    requires (!std::is_constructible_v<T, StringW> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    bool operator <(T const rhs) const noexcept {
        if constexpr (std::is_constructible_v<std::u16string_view, T> && !std::is_same_v<T, std::u16string_view>)
            return il2cpp_utils::detail::strless(inst, std::u16string_view(rhs));
        else if constexpr (std::is_constructible_v<std::string_view, T> && !std::is_same_v<T, std::string_view>)
            return il2cpp_utils::detail::strless(inst, std::string_view(rhs));
        else return il2cpp_utils::detail::strless(inst, rhs);
    }

    template<int sz>
    constexpr bool operator ==(ConstString<sz> const& rhs) const noexcept {
        Il2CppChar* first = inst->chars;
        char16_t const* second = rhs.chars;
        Il2CppChar* firstEnd = first + inst->length;
        char16_t const* secondEnd = second + sz - 1;

        while (first != firstEnd && second != secondEnd)
        {
            if (*first != *second) return false;
            first++; second++;
        }

        return first == firstEnd && second == secondEnd;
    }
    
    bool operator ==(StringW const& rhs) const noexcept;
    template<typename T>
    requires (!std::is_constructible_v<T, StringW> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    bool operator ==(T const rhs) const noexcept {
        if constexpr (std::is_constructible_v<std::u16string_view, T> && !std::is_same_v<T, std::u16string_view>)
            return il2cpp_utils::detail::strcomp(inst, std::u16string_view(rhs));
        else if constexpr (std::is_constructible_v<std::string_view, T> && !std::is_same_v<T, std::string_view>)
            return il2cpp_utils::detail::strcomp(inst, std::string_view(rhs));
        else return il2cpp_utils::detail::strcomp(inst, rhs);
    }

    bool starts_with(StringW const& rhs) const noexcept;
    template<typename T>
    requires (!std::is_constructible_v<T, StringW> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    bool starts_with(T const rhs) const noexcept {
        if constexpr (std::is_constructible_v<std::u16string_view, T> && !std::is_same_v<T, std::u16string_view>)
            return il2cpp_utils::detail::strstart(inst, std::u16string_view(rhs));
        else if constexpr (std::is_constructible_v<std::string_view, T> && !std::is_same_v<T, std::string_view>)
            return il2cpp_utils::detail::strstart(inst, std::string_view(rhs));
        else return il2cpp_utils::detail::strstart(inst, rhs);
    }
    
    bool ends_with(StringW const& rhs) const noexcept;
    template<typename T>
    requires (!std::is_constructible_v<T, StringW> && (std::is_constructible_v<std::u16string_view, T> || std::is_constructible_v<std::string_view, T>))
    bool ends_with(T const rhs) const noexcept {
        if constexpr (std::is_constructible_v<std::u16string_view, T> && !std::is_same_v<T, std::u16string_view>)
            return il2cpp_utils::detail::strend(inst, std::u16string_view(rhs));
        else if constexpr (std::is_constructible_v<std::string_view, T> && !std::is_same_v<T, std::string_view>)
            return il2cpp_utils::detail::strend(inst, std::string_view(rhs));
        else return il2cpp_utils::detail::strend(inst, rhs);
    }
    
    // who needs bounds checking amiright
    constexpr const Il2CppChar& operator [](size_t const& idx) const { return inst->chars[idx]; }
    constexpr Il2CppChar& operator [](size_t const& idx) { return inst->chars[idx]; }
    operator std::string() const;
    operator std::u16string() const;
    operator std::wstring() const;
    operator std::u16string_view();
    operator std::u16string_view const() const;

    private:
    Il2CppString* inst;
};
static_assert(sizeof(StringW) == sizeof(void*));
DEFINE_IL2CPP_DEFAULT_TYPE(StringW, string);
NEED_NO_BOX(StringW);
