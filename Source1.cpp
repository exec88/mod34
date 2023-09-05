#include <type_traits>
#include <string>

template <typename T>
concept ComplexConcept = requires(T type) {
    // ����������� 1: ������� ������ hash() � ������������ �����, �������������� � long
    { type.hash() } -> std::convertible_to<long>;

    // ����������� 2: ������� ������ toString() � ������������ ����� std::string
    { type.toString() } -> std::same_as<std::string>;

    // ����������� 3: ���������� ������������ �����������
    requires !std::has_virtual_destructor<T>;
};


//������ �� ������� ������������ ���� ������� ��� �������� ����������� ���� T :

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