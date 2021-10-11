#ifdef TEST_STRING
#include "../../shared/utils/il2cpp-utils.hpp"

static bool test1() {
    using namespace il2cpp_utils;
    static auto cs1 = newcsstr<CreationType::Manual>("test");
    auto cs2 = newcsstr("test2");
    return CRASH_UNLESS(RunMethod<bool>(cs1, "Equals", cs2));
}
#endif