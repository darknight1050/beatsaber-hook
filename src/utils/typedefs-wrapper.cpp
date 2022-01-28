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

    Il2CppString* strappend(Il2CppString const* lhs, Il2CppString const* rhs) noexcept {
        if (!lhs && !rhs) return il2cpp_functions::string_new_utf16(u"", 0);

        if (!lhs && rhs)
            return il2cpp_functions::string_new_utf16(rhs->chars, rhs->length);
        else if (lhs && !rhs)
            return il2cpp_functions::string_new_utf16(lhs->chars, lhs->length);
        else
        {
            size_t fullLength = lhs->length + rhs->length;
            auto result = il2cpp_functions::string_new_utf16(lhs->chars, fullLength);
            Il2CppChar* pastFirstString = result->chars + lhs->length;
            memcpy(pastFirstString, rhs->chars, rhs->length);
            return result;
        }
    }

    Il2CppString* strappend(Il2CppString const* lhs, std::u16string_view const rhs) noexcept {
        if (lhs)
        {
            size_t fullLength = lhs->length + rhs.size();
            auto result = il2cpp_functions::string_new_utf16(lhs->chars, fullLength);
            Il2CppChar* pastFirstString = result->chars + lhs->length;
            memcpy(pastFirstString, rhs.data(), rhs.size());
            return result;
        }
        else
        {
            return alloc_str(rhs);
        }
    }

    Il2CppString* strappend(Il2CppString const* lhs, std::string_view const rhs) noexcept {
        if (lhs)
        {
            size_t fullLength = lhs->length + rhs.size();
            il2cpp_functions::Init();
            Il2CppString* result = il2cpp_functions::string_new_utf16(lhs->chars, fullLength);
            Il2CppChar* pastFirstString = result->chars + lhs->length;
            convstr(rhs.data(), pastFirstString, rhs.size());
            return result;
        }
        else
        {
            return alloc_str(rhs);
        }
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

StringW::operator std::u16string_view const() const {
    return {inst->chars, static_cast<std::size_t>(inst->length)};
}

StringW::operator std::u16string_view() {
    return {inst->chars, static_cast<std::size_t>(inst->length)};
}

bool StringW::operator ==(StringW const& rhs) const noexcept {
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

bool StringW::operator <(StringW const& rhs) const noexcept {
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


bool StringW::starts_with(StringW const& rhs) const noexcept {
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


bool StringW::ends_with(StringW const& rhs) const noexcept {
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
