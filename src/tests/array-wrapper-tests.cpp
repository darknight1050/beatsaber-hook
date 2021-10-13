#ifdef TEST_ARRAY

#include "../../shared/utils/typedefs-array.hpp"
#include <iostream>

static void constDoThing(const ArrayW<int>& wrap) {
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
    ArrayW<int> arr(5);
    ArrayW<int> arr2(arr);
    // Init the pointer to nullptr
    ArrayW<int*> arr3{nullptr};
    auto i = arr[0];
    assert(arr.Length() == 5);
    assert(arr2.Length() == 5);
    for (auto itr : arr) {
        // do thing with each int
        assert(itr == i);
        std::cout << itr << std::endl;
    }
    for (auto itr : arr2) {
        // do thing with each int
        assert(itr == i);
        std::cout << itr << std::endl;
    }
    std::cout << arr.Length() << std::endl;
    std::cout << static_cast<Array<int*>*>(arr3) << std::endl;
    // Should be allowed to cast back
    std::cout << static_cast<Array<int>*>(arr) << std::endl;
    std::cout << i << std::endl;
}

#include "../../shared/utils/il2cpp-utils.hpp"

static void doThing2() {
    ArrayW<int> arr(2);
    MethodInfo info;
    il2cpp_utils::RunMethodThrow(static_cast<Il2CppObject*>(nullptr), &info, arr);
    il2cpp_utils::RunMethodThrow<ArrayW<Il2CppObject*>>(static_cast<Il2CppObject*>(nullptr), &info);
}

#endif