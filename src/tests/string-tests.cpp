#ifdef TEST_STRING
#include "../../shared/utils/il2cpp-utils.hpp"

static bool test1() {
    using namespace il2cpp_utils;
    static auto cs1 = newcsstr<CreationType::Manual>("test");
    auto cs2 = newcsstr("test2");
    return CRASH_UNLESS(RunMethod<bool>(cs1, "Equals", cs2));
}

#include "../../shared/utils/typedefs-string.hpp"
static_assert(sizeof(StringW) == sizeof(void*));
static_assert(il2cpp_utils::has_il2cpp_conversion<StringW>);
static_assert(sizeof(Il2CppString) == sizeof(ConstString<0>));

static void test2() {
    // construction
    ConstString one("one");
    ConstString two(u"two");
    ConstString copOne(one);
    ConstString moveTwo(std::move(two));
    StringW w1("test1");
    StringW w2(u"test2");
    StringW w3(nullptr);
    StringW w4((void*)nullptr);
    StringW w5((Il2CppString*)nullptr);
    StringW w6(one);
    StringW w7(moveTwo);
    // usage
    one->chars;
    std::string oneS(one);
    std::u16string twoS(moveTwo);
    std::wstring threeS(copOne);
    std::u16string_view fourS(copOne);
    Il2CppString* v1(one);

    w1->chars;
    std::string w1s(w1);
    std::u16string w2s(w2);
    std::wstring w3s(w3);
    std::u16string_view w6s(w6);
    Il2CppString* v2(w1);

    using namespace il2cpp_utils;
    RunMethod<bool>((Il2CppString*)w1, "Equals", w2);
}
#endif