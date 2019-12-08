#ifndef METAPROG_ARGS_H
#define METAPROG_ARGS_H

template<typename...Tail>
class ArgsPack;

template<>
class ArgsPack<> {
public:
    ArgsPack() {}

    template<class Func, typename... Args>
    auto apply(const Func &func, Args... args) -> decltype(func(args...)) {
        return func(args...);
    }
};


template<typename Head, typename... Tail>
class ArgsPack<Head, Tail...> {
private:
    typedef ArgsPack<Tail...> Rest;
    Rest rest;
    Head arg;

    template<typename T>
    T *asPtr(T &t) {
        return &t;
    }

    template<typename T>
    T *asPtr(T *t) {
        return t;
    }

    template<typename T>
    T &asRef(T &t) {
        return t;
    }

    template<typename T>
    T &asRef(T *t) {
        return *t;
    }

public:

    explicit ArgsPack(Head head, Tail... tail)
            : rest(tail...),
              arg(head) {}

    template<class Func, typename... Args>
    auto apply(const Func &func, Args... args) -> decltype(rest.apply(func, args..., asRef(arg))) {
        return rest.apply(func, args..., asRef(arg));
    }

    template<class Func, typename... Args>
    auto apply(const Func &func, Args... args) -> decltype(rest.apply(func, args..., asPtr(arg))) {
        return rest.apply(func, args..., asPtr(arg));
    }

};


#endif //METAPROG_ARGS_H
