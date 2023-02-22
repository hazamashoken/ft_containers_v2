#include <iomanip>
#include <iostream>
#include <vector>
#include <exception>
#include "../../../vector.hpp"

#ifdef FT
    using namespace ft;
#else
    using namespace std;
#endif

template<typename T>
void printVector(vector<T>& v)
{
    std::cout << "Vector: ";
    for (typename vector<T>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void head(std::string s)
{
    std::cout << std::endl;
    std::cout << std::setw(100) << std::setfill('=') << std::left << s + " " << std::endl;
    std::cout << std::endl;
}

void tail(void)
{
    std::cout << std::setw(100) << std::setfill('=') << std::right << " END" << std::endl;
    std::cout << std::endl;
}

int main(void)
{
    vector<std::string> a(1, "hello");
    a.resize(2, "world");
    a.resize(3, "this");
    a.resize(4, "is");
    a.resize(5, "me");

    head("Operator[]");
    // Test operator[]
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << a[i] << std::endl;
    }
    tail();

    head("At");
    /// Test at
    for (size_t i = 0; i < 10; i++)
    {
        try
        {
            std::cout << a.at(i) << std::endl;
        }
        catch (std::exception& e)
        {
            std::cout << "Exception Caught" << std::endl;
        }
    }
    tail();

    head("Front");
    /// Test front
    std::cout << a.front() << std::endl;
    tail();

    head("Back");
    /// Test back
    std::cout << a.back() << std::endl;
    tail();

    head("Data");
    vector<std::string> b;
    /// Test data
    /// With Regular data
    std::cout << *a.data() << std::endl;

    /// With nullptr
    std::cout << b.data() << std::endl;
    tail();

    return (0);
}
