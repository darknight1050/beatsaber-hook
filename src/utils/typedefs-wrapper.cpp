#include "../../shared/utils/typedefs-wrappers.hpp"
#include "../../shared/utils/typedefs-string.hpp"
#include "../../shared/utils/il2cpp-functions.hpp"
#include "../../shared/utils/typedefs.h"

std::unordered_map<void*, size_t> Counter::addrRefCount;
std::shared_mutex Counter::mutex;

namespace detail {
    static std::codecvt_utf8_utf16<char16_t> conv;

    void convstr(char const* inp, char16_t* outp, int sz) {
        std::mbstate_t state;
        conv.in(state, inp, inp + sz, inp, outp, outp + sz, outp);
        outp[sz] = '\0';
    }
    void convstr(char16_t const* inp, char* outp, int sz) {
        std::mbstate_t state;
        conv.out(state, inp, inp + sz, inp, outp, outp + sz, outp);
        outp[sz] = '\0';
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

StringW::operator std::string() {
    std::string val;
    val.reserve(inst->length);
    detail::convstr(inst->chars, val.data(), inst->length);
    return val;
}

StringW::operator std::u16string() {
    return {inst->chars, inst->chars + inst->length + 1};
}

StringW::operator std::wstring() {
    return {inst->chars, inst->chars + inst->length + 1};
}

StringW::operator std::u16string_view() {
    return {inst->chars, static_cast<std::size_t>(inst->length)};
}
