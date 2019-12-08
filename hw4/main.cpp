#include <iostream>
#include "functor.h"

int function(int, float, short) {
    return 42;
};

class Y {
public:
    Y() = default;
};

class X {
public:
    X() = default;

    float process(Y &y) { return 3.14; };
};

int main() {

    // обычные функции
    auto functor1 = makeFunctor(&function, 1, 2, 3);
    int val1 = functor1.call();

    // функции-члены
    auto functor2 = makeFunctor(&X::process, Y());
    X x;
    float val2 = functor2.call(x);

    // лямбды
    Y y;
    auto functor3 = makeFunctor([](Y *) { return 1; }, y);
    auto val3 = functor3.call();

    std::cout << val1 << std::endl
              << val2 << std::endl
              << val3 << std::endl;
    return 0;
}