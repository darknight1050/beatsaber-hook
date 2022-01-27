#include "../../shared/utils/typedefs-wrappers.hpp"
#include "../../shared/utils/typedefs-string.hpp"
#include "../../shared/utils/il2cpp-functions.hpp"
#include "../../shared/utils/typedefs.h"
#include <locale>
#include <string.h>

std::unordered_map<void*, size_t> Counter::addrRefCount;
std::shared_mutex Counter::mutex;

typedef char16_t Il2CppChar;
namespace il2cpp_utils {
namespace detail {
    template<class Facet>
    struct deletable_facet : Facet {
        template<class ...Args>
        deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
        ~deletable_facet() {}
    };

    // Note that char is actually required here over char8_t-- this is due to NDK not having a char8_t specialization for this yet.
    deletable_facet<std::codecvt<char16_t, char, std::mbstate_t>> conv;

    void convstr(char const* inp, char16_t* outp, int sz) {
        std::mbstate_t state;
        char const* from_next;
        char16_t* to_next;
        conv.in(state, inp, inp + sz, from_next, outp, outp + sz, to_next);
        *to_next = '\0';
    }
    std::size_t convstr(char16_t const* inp, char* outp, int isz, int osz) {
        std::mbstate_t state;
        char16_t const* from_next;
        char* to_next;
        auto convOut = conv.out(state, inp, inp + isz, from_next, outp, outp + osz, to_next);
        if (convOut != std::codecvt_base::ok) {
            throw convOut;
        }
        *to_next = '\0';
        return (std::size_t)(to_next - 1 - outp);
    }

    Il2CppString* alloc_str(std::string_view str) {
        il2cpp_functions::Init();
        return il2cpp_functions::string_new_len(str.data(), str.size());
    }
    Il2CppString* alloc_str(std::u16string_view str) {
        il2cpp_functions::Init();
        return il2cpp_functions::string_new_utf16((Il2CppChar const*) str.data(), str.size());
    }
}
}

StringW::operator std::string() const {
    std::string val(inst->length * 2, '\0');
    auto resSize = il2cpp_utils::detail::convstr(inst->chars, val.data(), inst->length, val.size());
    val.resize(resSize);
    return val;
}

StringW::operator std::u16string() const {
    return {inst->chars, inst->chars + inst->length};
}

StringW::operator std::wstring() const {
    return {inst->chars, inst->chars + inst->length};
}

StringW::operator const std::u16string_view() const {
    return {inst->chars, static_cast<std::size_t>(inst->length)};
}

StringW::operator std::u16string_view() {
    return {inst->chars, static_cast<std::size_t>(inst->length)};
}

bool strcomp(Il2CppString const* lhs, const std::u16string_view rhs) noexcept {
    if (!lhs || lhs->length != (int)rhs.size()) return false;

    Il2CppChar const* first = lhs->chars; 
    auto* second = rhs.data(); 
    Il2CppChar const* firstEnd = first + lhs->length; 
    auto* secondEnd = second + (int)rhs.size(); 

    while (first != firstEnd && second != secondEnd)
    {
        if (*first != *second) return false;
        first++; second++;
    }

    return first == firstEnd && second == secondEnd;
}

bool strcomp(Il2CppString const* lhs, const std::string_view rhs) noexcept {
    if (!lhs || lhs->length != (int)rhs.size()) return false;

    Il2CppChar const* first = lhs->chars; 
    auto* second = rhs.data(); 
    Il2CppChar const* firstEnd = first + lhs->length; 
    auto* secondEnd = second + (int)rhs.size(); 

    while (first != firstEnd && second != secondEnd)
    {
        if (*first != *second) return false;
        first++; second++;
    }

    return first == firstEnd && second == secondEnd;
}

bool strless(Il2CppString const* lhs, const std::string_view rhs) noexcept {
    if (!lhs) return true;

    Il2CppChar const* first = lhs->chars; 
    char const* second = rhs.data(); 
    Il2CppChar const* firstEnd = lhs->chars + lhs->length; 
    char const* secondEnd = rhs.data() + (int)rhs.size(); 
    
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

bool strless(Il2CppString const* lhs, const std::u16string_view rhs) noexcept {
    if (!lhs) return true;

    Il2CppChar const* first = lhs->chars; 
    char16_t const* second = rhs.data(); 
    Il2CppChar const* firstEnd = first + lhs->length; 
    char16_t const* secondEnd = second + (int)rhs.size(); 
    
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

StringW strappend(Il2CppString const* lhs, const std::string_view rhs) noexcept {
    return std::u16string(lhs->chars, lhs->chars + lhs->length).append(std::u16string(rhs.data(), rhs.data() + rhs.size()));
}

StringW strappend(Il2CppString const* lhs, const std::u16string_view rhs) noexcept {
    return std::u16string(lhs->chars, lhs->chars + lhs->length).append(rhs);
}

bool strstart(Il2CppString const* lhs, const std::string_view rhs) noexcept {
    if (!lhs || lhs->length < (int)rhs.size()) return false;

    Il2CppChar const* first = lhs->chars; 
    char const* second = rhs.data(); 
    char const* secondEnd = second + (int)rhs.size(); 
    
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

bool strstart(Il2CppString const* lhs, const std::u16string_view rhs) noexcept {
    if (!lhs || lhs->length < (int)rhs.size()) return false;

    Il2CppChar const* first = lhs->chars; 
    char16_t const* second = rhs.data(); 
    char16_t const* secondEnd = second + (int)rhs.size(); 
    
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

bool strend(Il2CppString const* lhs, const std::string_view rhs) noexcept {
    if (!lhs || lhs->length < (int)rhs.size()) return false;

    Il2CppChar const* first = lhs->chars + lhs->length - 1;
    char const* secondBegin = rhs.data() - 1; 
    char const* second = secondBegin + (int)rhs.size(); 
    
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
bool strend(Il2CppString const* lhs, const std::u16string_view rhs) noexcept {
    if (!lhs || lhs->length < (int)rhs.size()) return false;

    Il2CppChar const* first = lhs->chars + lhs->length - 1;
    char16_t const* secondBegin = rhs.data() - 1; 
    char16_t const* second = secondBegin + (int)rhs.size(); 
    
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

bool StringW::operator ==(StringW rhs) const noexcept {
    if (inst == rhs.inst) return true;
    if (!inst || !rhs || inst->length != rhs->length) return false;
    
    Il2CppChar const* first = inst->chars; 
    Il2CppChar const* second = rhs->chars; 
    Il2CppChar const* firstEnd = first + inst->length; 
    Il2CppChar const* secondEnd = second + rhs->length; 
    
    while (first != firstEnd && second != secondEnd)
    {
        if (*first != *second) return false;
        first++; second++;
    }

    return first == firstEnd && second == secondEnd;
}

bool StringW::operator <(StringW rhs) const noexcept {
    if (!inst && !rhs) return false;
    if (!inst) return true;
    if (!rhs) return false;
    
    Il2CppChar const* first = inst->chars; 
    Il2CppChar const* second = rhs->chars; 
    Il2CppChar const* firstEnd = first + inst->length; 
    Il2CppChar const* secondEnd = second + rhs->length; 
    
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


bool StringW::starts_with(StringW rhs) const noexcept {
    // if either instance is nullptr, return false, if our length is smaller than prefix length, also return false
    if (!inst || !rhs || inst->length < rhs->length) return false;

    Il2CppChar const* first = inst->chars; 
    Il2CppChar const* second = rhs->chars; 
    Il2CppChar const* secondEnd = second + rhs.inst->length; 
    
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


bool StringW::ends_with(StringW rhs) const noexcept {
    if (!inst || !rhs || inst->length < rhs->length) return false;

    Il2CppChar const* first = inst->chars + inst->length - 1;
    Il2CppChar const* secondBegin = rhs->chars - 1; 
    Il2CppChar const* second = secondBegin + rhs->length; 
    
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
