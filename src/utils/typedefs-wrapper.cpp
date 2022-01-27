#include "../../shared/utils/typedefs-wrappers.hpp"
#include "../../shared/utils/typedefs-string.hpp"
#include "../../shared/utils/il2cpp-functions.hpp"
#include "../../shared/utils/typedefs.h"
#include <locale>
#include <string.h>

std::unordered_map<void*, size_t> Counter::addrRefCount;
std::shared_mutex Counter::mutex;

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
        return il2cpp_functions::string_new_utf16((Il2CppChar*) str.data(), str.size());
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

bool StringW::operator ==(const StringW& rhs) const {
    if (inst == rhs.inst) return true;
    if (!inst || !rhs || inst->length != rhs.inst->length) return false;
    
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

bool StringW::operator ==(const std::string_view rhs) const {
    if (!inst || inst->length != (int)rhs.size()) return false;

    Il2CppChar* first = inst->chars; 
    char const* second = rhs.data(); 
    Il2CppChar* firstEnd = first + inst->length; 
    char const* secondEnd = second + rhs.size(); 
    
    while (first != firstEnd && second != secondEnd)
    {
        if (*first != *second) return false;
        first++; second++;
    }

    return first == firstEnd && second == secondEnd;
}

bool StringW::operator ==(const std::u16string_view rhs) const {
    if (!inst || inst->length != (int)rhs.size()) return false;

    Il2CppChar* first = inst->chars; 
    char16_t const* second = rhs.data(); 
    Il2CppChar* firstEnd = inst->chars + inst->length; 
    char16_t const* secondEnd = second + rhs.size(); 
    
    while (first != firstEnd && second != secondEnd)
    {
        if (*first != *second) return false;
        first++; second++;
    }

    return first == firstEnd && second == secondEnd;
}

bool StringW::operator <(const StringW& rhs) const {
    if (!inst && !rhs) return false;
    if (!inst) return true;
    if (!rhs) return false;
    
    Il2CppChar* first = inst->chars; 
    Il2CppChar* second = rhs.inst->chars; 
    Il2CppChar* firstEnd = first + inst->length; 
    Il2CppChar* secondEnd = second + rhs.inst->length; 
    
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

bool StringW::operator <(const std::string_view rhs) const {
    if (!inst) return true;

    Il2CppChar* first = inst->chars; 
    char const* second = rhs.data(); 
    Il2CppChar* firstEnd = inst->chars + inst->length; 
    char const* secondEnd = rhs.data() + rhs.size(); 
    
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

bool StringW::operator <(const std::u16string_view rhs) const {
    if (!inst) return true;

    Il2CppChar* first = inst->chars; 
    char16_t const* second = rhs.data(); 
    Il2CppChar* firstEnd = first + inst->length; 
    char16_t const* secondEnd = second + rhs.size(); 
    
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


