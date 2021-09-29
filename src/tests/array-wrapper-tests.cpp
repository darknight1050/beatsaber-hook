#ifdef TEST_ARRAY

#include "../../shared/utils/typedefs.h"
#include "../../shared/utils/il2cpp-utils.hpp"
#include <iostream>

static void constDoThing(const ArrayWrapper<int>& wrap) {
    auto i = wrap[0];
    assert(wrap.Length() == 5);
    for (auto itr : wrap) {
        // do thing with each int, const
        assert(itr == i);
        std::cout << itr << std::endl;
    }
    std::cout << i << std::endl;
}

static void doThing() {
    ArrayWrapper<int> arr(5);
    auto i = arr[0];
    assert(arr.Length() == 5);
    for (auto itr : arr) {
        // do thing with each int
        assert(itr == i);
        std::cout << itr << std::endl;
    }
    // Should be allowed to cast back
    std::cout << static_cast<Array<int>*>(arr);
    std::cout << i << std::endl;
}

static void doThing2() {
    ArrayWrapper<int> arr(2);
    MethodInfo info;
    il2cpp_utils::RunMethodThrow(classof(Il2CppObject*), &info, arr);
    il2cpp_utils::RunMethodThrow<ArrayWrapper<Il2CppObject*>>(classof(Il2CppObject*), &info);
}

#endif