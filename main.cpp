#include <QCoreApplication>
#include <iostream>
#include <memory> // shared_ptr

void TestCpp11 (void);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello World!" << std::endl;

    TestCpp11();

    return 0; 
}

// override and final
class A
{
public:
    virtual std::string Name () const {return "A";};
};

class B : public A
{
public:
    std::string Name () const override final {return "B";};
};

class C : public B
{
public:
    // following will error out can't override virtual final
    //std::string Name () const {return "B";};

    // following will error also can't override virtual final
    //std::string Name () const override {return "B";};
};

void TestCpp11()
{

    std::cout << "C++ Version 11 Features" << std::endl;

    // Auto variable
    auto testNum = 1;
    std::cout << "Auto Number " << testNum << std::endl;

    std::vector<int> testVector;
    testVector.push_back(0);
    testVector.push_back(1);
    testVector.push_back(3);
    testVector.push_back(5);

    // Range loop
    for (auto val : testVector)
    {
        std::cout << "Vector " << val << std::endl;
    }

    // Test override final
    std::shared_ptr<A> clsPtr(new B);
    std::cout << "Override Class " << clsPtr->Name() << std::endl;

    // weak enum
    enum WeakEnum {one, two, three};
    WeakEnum weakEnum = one; // Notice no enum scope
    std::cout << "Weak enum " << weakEnum << std::endl;

    // Strongly typed enums
    enum class StrongEnum {one = 1, two, three};
    StrongEnum strongEnum = StrongEnum::one; // Notice enum scope
    if (StrongEnum::one == strongEnum)
    {
       std::cout << "Strong enum one" << std::endl;
    }

    // lambda or annonymous functions
    auto lambda = [](int n) {std::cout << "lambda n " << n << std::endl;};
    std::for_each(testVector.begin(), testVector.end(), lambda);

    // same functionality without variable
    std::for_each(testVector.begin(), testVector.end(), [](int n) {std::cout << "lambda n " << n << std::endl;});
}
