#include <type_traits>
#include <string>

template <typename T>
concept ComplexConcept = requires(T type) {
    // Ограничение 1: Наличие метода hash() с возвращаемым типом, конвертируемым в long
    { type.hash() } -> std::convertible_to<long>;

    // Ограничение 2: Наличие метода toString() с возвращаемым типом std::string
    { type.toString() } -> std::same_as<std::string>;

    // Ограничение 3: Отсутствие виртуального деструктора
    requires !std::has_virtual_destructor<T>;
};


//Теперь вы сможете использовать этот концепт для проверки ограничений типа T :

class MyType {
public:
    long hash() { return 42; }
    std::string toString() { return "MyType"; }
};

class AnotherType {
public:
    long hash() { return 123; }
    std::string toString() { return "AnotherType"; }
    virtual ~AnotherType() {}
};

static_assert(ComplexConcept<MyType>);
static_assert(!ComplexConcept<AnotherType>);