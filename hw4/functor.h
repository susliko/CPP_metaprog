#ifndef METAPROG_FUNCTOR_H
#define METAPROG_FUNCTOR_H

#include "args.h"

template<typename Object, typename Func>
class MemberFuncWrapper {
private:
    Object &instance;
    Func func;
public:
    MemberFuncWrapper(Object &instance, const Func &func)
            : instance(instance), func(func) {}

    template<typename... Args>
    auto operator()(Args... args) const -> decltype((instance.*func)(args...)) {
        return (instance.*func)(args...);
    }
};

template<typename Func>
class FuncWrapper {
private:
    Func func;
public:
    FuncWrapper(const Func &func) : func(func) {}

    template<typename... Args>
    auto operator()(Args... args) const -> decltype(func(args...)) {
        return func(args...);
    }
};

template<typename Func, typename... Args>
class Functor {
private:
    typedef ArgsPack<Args...> PackedArgs;
    Func func;
    PackedArgs args;

public:
    explicit Functor(Func func, Args... args) : func(func), args(args...) {}

    template<typename Function = Func>
    auto call() -> decltype(args.apply(FuncWrapper<Function>(func))) const {
        return args.apply(func);
    }

    template<typename Object>
    auto call(Object &instance) -> decltype(args.apply(MemberFuncWrapper<Object, Func>(instance, func))) const {
        return args.apply(MemberFuncWrapper<Object, Func>(instance, func));
    }

};

template<typename Func, typename... Args>
Functor<Func, Args...> makeFunctor(Func func,
                                   Args... args) {
    return Functor<Func, Args...>(func, args...);
}


#endif //METAPROG_FUNCTOR_H
