#include <iostream>
#include <vector>

template<typename A, typename B>
struct Eq {
    static const bool value = false;
};

template<typename A>
struct Eq<A, A> {
    static const bool value = true;
};

template<typename A, typename B>
bool typesEqual() {
    return Eq<A, B>::value;
}

struct unused;
// `Type` is checked for occurrences in the list of types `First, Rest...`
template<typename Type, typename T0 = unused, typename T1 = unused,
        typename T2 = unused, typename T3 = unused,
        typename T4 = unused, typename T5 = unused,
        typename T6 = unused, typename T7 = unused>
struct IndexOfType
{
    static std::vector<int> value() {
        std::vector<int> indices;
        if (typesEqual<Type, T0>()) indices.push_back(0);
        if (typesEqual<Type, T1>()) indices.push_back(1);
        if (typesEqual<Type, T2>()) indices.push_back(2);
        if (typesEqual<Type, T3>()) indices.push_back(3);
        if (typesEqual<Type, T4>()) indices.push_back(4);
        if (typesEqual<Type, T5>()) indices.push_back(5);
        if (typesEqual<Type, T6>()) indices.push_back(6);
        if (typesEqual<Type, T7>()) indices.push_back(7);
        if (indices.empty()) indices.push_back(-1);
        return indices;
    }
};

void printVector(std::vector<int>& v) {
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {

    std::vector<int> index1 = IndexOfType<int, int>::value(); // [0]
    std::vector<int> index2 = IndexOfType<int, char, double, int, std::string, int, char, int>::value(); // [2, 4, 6]
    std::vector<int> index3 = IndexOfType<int, double, std::string>::value(); // [-1]

    printVector(index1);
    printVector(index2);
    printVector(index3);

    return 0;
}
