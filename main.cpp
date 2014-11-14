#include <QCoreApplication>
#include <iostream>
#include <memory> // shared_ptr
#include <thread>
#include <mutex>

void TestCpp11 (void);
void TestCpp11Threads (void);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello World!" << std::endl;

    TestCpp11();

    TestCpp11Threads();

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
}

class TestThreadClass
{
public:
    int mClassCount;
    int mThreadCount;
    std::mutex mMutex;

    TestThreadClass ()
    {
        mThreadCount = 0;
        mClassCount = 0;
    }

    void RunThreadFunction ()
    {
        const int maxCount = 10000000;
        mThreadCount++;
        // Wait for second thread
        while (mThreadCount != 2);

        for(auto i = 1; i <= maxCount; i++)
        {
            {
                // without this lock we get differences in values
                std::lock_guard<std::mutex> lock(mMutex);

                mClassCount = mClassCount + 1;
                auto temp = mClassCount;
                if (temp != mClassCount || i % (maxCount / 10) == 0)
                {
                    auto match = (temp == mClassCount) ? "match " : "Diff ";
                    std::cout << match << std::this_thread::get_id() << " mClassCount: " << mClassCount <<
                             " temp: " << temp << std::endl;
                }
            }
        }
    }
};

void TestCpp11Threads(void)
{
    TestThreadClass threadClass;

    std::thread myThread(&TestThreadClass::RunThreadFunction, &threadClass);
    std::thread my2Thread(&TestThreadClass::RunThreadFunction, &threadClass);

    myThread.join();
    my2Thread.join();
}
