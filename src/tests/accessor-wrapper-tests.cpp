#ifdef TEST_WRAPPER

#include "../../shared/utils/accessor-wrapper-types.hpp"

#include <iostream>


struct Underlying {
    int a;
    int b;
    int c;
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
    return t.A == 0x4567 && t.B == 0x1234 && t.c == 123;
}
#endif