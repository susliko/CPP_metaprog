#include <iostream>

struct NullType {
};

template<class Head, class Tail>
struct Typelist {};

template<class TList, template<class> class Unit>
class GenScatterHierarchy;

template<class T1, class T2, template<class> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
        : public GenScatterHierarchy<T1, Unit>
        , public GenScatterHierarchy<T2, Unit> {
public:
    using TList = Typelist<T1, T2>;
    using LeftBase = GenScatterHierarchy<T1, Unit>;
    using RightBase = GenScatterHierarchy<T2, Unit>;
    template<class T>
    struct Rebind {
        using Result = Unit<T>;
    };
};

template<class AtomicType, template<class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType> {
public:
    using LeftBase = Unit<AtomicType>;
    template<class T>
    struct Rebind {
        using Result = Unit<T>;
    };
};

template<template<class> class Unit>
class GenScatterHierarchy<NullType, Unit> {
    template<class T>
    struct Rebind {
        using Result = Unit<T>;
    };
};


template<class T>
struct Holder {
    T value;
};

using WidgetInfo = GenScatterHierarchy<Typelist<int, Typelist<std::string, double>>, Holder>;

template<class T, class Hierarchy>
typename Hierarchy::template Rebind<T>::Result &Field(Hierarchy &hierarchy) {
    return hierarchy;
}

int main() {
    WidgetInfo widgetInfo;
    Field<int>(widgetInfo).value = 42;
    Field<std::string>(widgetInfo).value = "Kek";
    Field<double>(widgetInfo).value = 3.14;
    std::cout << Field<int>(widgetInfo).value << std::endl;
    std::cout << Field<std::string>(widgetInfo).value << std::endl;
    std::cout << Field<double>(widgetInfo).value << std::endl;
    return 0;
}
