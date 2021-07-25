#ifdef TEST_BYREF
#include "../../shared/utils/byref.hpp"
#include "../../shared/utils/il2cpp-utils.hpp"
#include "../../shared/utils/typedefs.h"

static void test() {
    MethodInfo inf;
    int x = 3;
    il2cpp_utils::RunMethod((Il2CppClass*)nullptr, &inf, byref(x));
    il2cpp_utils::RunMethodThrow((Il2CppClass*)nullptr, &inf, byref(x));
    il2cpp_utils::RunStaticMethod(&inf, byref(x));
    il2cpp_utils::ExtractIndependentType<ByRef<int>>();
    il2cpp_utils::ExtractIndependentType<int>();
    il2cpp_utils::ExtractIndependentType<int&>() == il2cpp_utils::ExtractIndependentType<ByRef<int&>>();
}
#endif
