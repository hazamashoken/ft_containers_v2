#include <iomanip>
#include <iostream>
#include <vector>
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
    vector<float> a;
    vector<float> b(10, 4.2);

    head("Size");
    /// Test Size
    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Size b: " << b.size() << std::endl;
    tail();

    head("Max size");
    /// Test Max size
    std::cout << "Max size a: " << a.max_size() << std::endl;
    std::cout << "Max size b: " << b.max_size() << std::endl;
    tail();

    head("Capacity");
    /// Test Capacity
    std::cout << "Capacity a: " << a.capacity() << std::endl;
    std::cout << "Capacity b: " << b.capacity() << std::endl;
    tail();

    head("Empty");
    /// Test Empty
    std::cout << "Empty a: " << a.empty() << std::endl;
    std::cout << "Empty b: " << b.empty() << std::endl;
    tail();

    /// Test Resize
    head("Resize");
    /// Resize to > size, capacity with default val
    a.resize(2);
    printVector<float>(a);
    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Capacity a:" << a.capacity() << std::endl;

    /// Resize to > size, capacity with 42 value
    a.resize(20, 42);
    printVector<float>(a);
    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Capacity a:" << a.capacity() << std::endl;

    /// Resize to < size with default val
    b.resize(5);
    printVector<float>(b);
    std::cout << "Size b: " << b.size() << std::endl;
    std::cout << "Capacity b:" << b.capacity() << std::endl;

    /// Resize to < size with some val
    b.resize(1, 0.33);
    printVector<float>(b);
    std::cout << "Size b: " << b.size() << std::endl;
    std::cout << "Capacity b:" << b.capacity() << std::endl;

    /// Resize to > size but < capacity with default val
    b.resize(4, 3.14);
    printVector<float>(b);
    std::cout << "Size b: " << b.size() << std::endl;
    std::cout << "Capacity b:" << b.capacity() << std::endl;

    /// Resize to > size but < capacity with some val
    b.resize(10, 555);
    printVector<float>(b);
    std::cout << "Size b: " << b.size() << std::endl;
    std::cout << "Capacity b:" << b.capacity() << std::endl;
    tail();

    head("Reserve");
    /// Test Reserve
    a.reserve(0);
    printVector<float>(a);
    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Capacity a:" << a.capacity() << std::endl;

    a.reserve(20);
    printVector<float>(a);
    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Capacity a:" << a.capacity() << std::endl;

    vector<float> c;
    c.reserve(42);
    printVector<float>(c);
    std::cout << "Size c: " << c.size() << std::endl;
    std::cout << "Capacity c:" << c.capacity() << std::endl;

    a.reserve(50);
    printVector<float>(a);
    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Capacity a:" << a.capacity() << std::endl;
    tail();

    /// Shrink to fit Not in std c++98
    // a.resize(0);
    // printVector<float>(a);
    // std::cout << "Size a: " << a.size() << std::endl;
    // std::cout << "Capacity a:" << a.capacity() << std::endl;

    // a.shrink_to_fit();
    // printVector<float>(a);
    // std::cout << "Size a: " << a.size() << std::endl;
    // std::cout << "Capacity a:" << a.capacity() << std::endl;

    // a.resize(42, 42);
    // printVector<float>(a);
    // std::cout << "Size a: " << a.size() << std::endl;
    // std::cout << "Capacity a:" << a.capacity() << std::endl;

    // a.shrink_to_fit();
    // printVector<float>(a);
    // std::cout << "Size a: " << a.size() << std::endl;
    // std::cout << "Capacity a:" << a.capacity() << std::endl;
}
