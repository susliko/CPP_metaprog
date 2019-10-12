#include <iostream>
#include <tuple>
#include <sstream>
#include <vector>

template<typename Last>
Last readCSVline(std::istream &is, char delim) {
    Last last;
    is >> last;
    return last;
}

template<typename First, typename Second, typename... Rest>
std::tuple<First, Second, Rest...> readCSVline(std::istream &is, char delim) {
    std::string firstStr;
    std::getline(is, firstStr, delim);
    std::istringstream firstInput(firstStr);
    First first;
    firstInput >> first;

    std::tuple<First> firstTuple = std::make_tuple(first);
    std::tuple<Second, Rest...> restTuple = readCSVline<Second, Rest...>(is, delim);
    return std::tuple_cat(firstTuple, restTuple);
}

template<typename First, typename...Rest>
std::vector<std::tuple<First, Rest...>> readCSV(std::istream &is, char delim) {
    std::vector<std::tuple<First, Rest...>> lines;

    while (is.peek() != EOF) {
        lines.push_back(readCSVline<First, Rest...>(is, delim));
    }
    return lines;
}

class Human {
public:
    Human() = default;

    Human(std::string &name, int age) : name(name), age(age) {};

    std::string name;
    int age = 0;
};

std::istream &operator>>(std::istream &is, Human &human) {
    std::getline(is, human.name, ':');
    is >> human.age;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Human &human) {
    os << human.name << ":" << human.age;
    return os;
}

int main() {
    const char *simpleCSV =
            "a,foo,1,1\n"
            "b,bar,42,3.14\n"
            "c,buz,82,2.71\n";
    std::istringstream simpleCSVStream(simpleCSV);
    typedef std::vector<std::tuple<char, std::string, int, double>> SimpleType;
    SimpleType parsedSimple = readCSV<char, std::string, int, double>(simpleCSVStream, ',');
    std::cout << std::get<0>(parsedSimple[0]) << std::endl; // a
    std::cout << std::get<1>(parsedSimple[1]) << std::endl; // bar
    std::cout << std::get<3>(parsedSimple[2]) << std::endl; // 82


    const char *complexCSV =
            "teacher,Bob:24\n"
            "student,Alice:20\n";
    std::istringstream complexCSVStream(complexCSV);
    typedef std::vector<std::tuple<std::string, Human>> ComplexType;
    ComplexType parsedComplex = readCSV<std::string, Human>(complexCSVStream, ',');
    std::cout << std::get<0>(parsedComplex[0]) << std::endl; // teacher
    std::cout << std::get<1>(parsedComplex[0]) << std::endl; // Bob:24
    std::cout << std::get<0>(parsedComplex[1]) << std::endl; // student
    std::cout << std::get<1>(parsedComplex[1]) << std::endl; // Alice:20

    return 0;
}