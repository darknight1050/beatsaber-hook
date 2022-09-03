#ifdef TEST_WRAPPER

#include "../../shared/utils/accessor-wrapper-types.hpp"

#include <iostream>


struct Underlying {
    int a;
    int b;
    int c;
};

struct Test;

template<>
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Test> {
    static Il2CppClass* get() {
        return nullptr;
    }
};

struct Test {
    friend int main();
    // TODO: This explicit constructor should either not be a constructor at all (static method, and change concept to match)
    // or should be friended to a very specific case
    explicit Test(void* i) : instance(i) {
        std::cout << "test ctor: " << i << std::endl;
    }
    Test& assign(void* i) {
        // Called assign instead of assignment operator because it is dangerous!
        new (this) Test(i);
        return *this;
    }
    private:
    void* instance;
    public:
    bs_hook::InstanceProperty<"A", int, true, true> A{instance};
    bs_hook::InstanceProperty<"B", int, true, true> B{instance};
    bs_hook::InstanceField<int, 0x8, true> c{instance};
    static inline bs_hook::StaticField<int, "staticA", true, &::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Test>::get> staticA;
    static inline bs_hook::StaticField<int, "staticA2", false, &::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Test>::get> staticA2;
    static inline bs_hook::StaticProperty<int, "staticProp", true, true, &::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Test>::get> staticB;
    static inline bs_hook::StaticProperty<int, "staticProp2", true, false, &::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Test>::get> staticProp2;
    static inline bs_hook::StaticProperty<int, "staticProp3", false, true, &::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<Test>::get> staticProp3;
};

int main() {
    Test t(new Underlying());
    t.A = 0x4567;
    t.B = 0x1234;
    std::cout << std::endl;
    t.c = 123;
    std::cout << "A: " << t.A << " B: " << t.B << " c: " << t.c << std::endl;
    t.assign(new Underlying());
    std::cout << "A: " << t.A << " B: " << t.B << " c: " << t.c << std::endl;
    // return t.A == t.B;
    // return t.c;
    Test::staticA = 456;
    Test::staticB = 789;
    Test::staticA = Test::staticB;
    // Test::staticA2 = 123; // INVALID!
    // Test::staticProp2 = 123; // INVALID!
    // Test::staticB = Test::staticProp3; // INVALID!
    return t.A == 0x4567 && t.B == 0x1234 && t.c == 123;
}
#endif