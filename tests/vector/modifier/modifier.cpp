#include <iomanip>
#include <iostream>
#include <vector>
#include <exception>
#include <cstdlib>
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
    vector<char> a(5, 'B');
    vector<char> b(42, 'K');
    vector<char> c(21, 'K');
    vector<char> d(10, '!');
    vector<char> e;

    /**
     *  @brief Test for iterator assign
     */
    head("Range Assign");

    /// Test for Assign beyond capacity
    a.assign(b.begin(), b.end());
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;

    /// Test for Assign less than size and capacity
    a.assign(d.begin(), d.end());
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;

    a.assign(e.begin(), e.end());
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;

    /// Test for Assign greater than size but less than capacity
    a.assign(c.begin(), c.end());
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;
    tail();

    /**
     *  @brief Test for fill assign
     */
    head("Fill assign");
    /// Test for fill > size but <= capacity
    a.assign(42, 'f');
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;

    /// Test for fill beyond capacity
    a.assign(63, 'F');
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;

    /// Test for fill < size
    a.assign(10, 'O');
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;

    a.assign(0, '0');
    printVector<char>(a);
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Capacity: " << a.capacity() << std::endl;
    tail();

    /**
     *  @brief push_back test with room in vector and without room
     */
    head("Push back");
    vector<char> p;

    p.push_back('s');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('p');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('o');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('o');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('l');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('p');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('r');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('a');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    p.push_back('!');
    printVector<char>(p);
    std::cout << "Size: " << p.size() << std::endl;
    std::cout << "Capacity: " << p.capacity() << std::endl;
    tail();

    head("Pop back");
    for (int i = 0; i < 9; i++)
    {
        p.pop_back();
        printVector<char>(p);
        std::cout << "Size: " << p.size() << std::endl;
        std::cout << "Capacity: " << p.capacity() << std::endl;
    }
    tail();

    /**
     *  @defgroup Insert method
     */

    /**
     *  @brief Single element insert
     */

    head("Insert element");
    /// Insert to 0 capacity
    vector<int> i;
    vector<int>::iterator it = i.insert(i.end(), 5);
    printVector<int>(i);
    std::cout << "Return: " << *it << std::endl;
    std::cout << "Size: " << i.size() << std::endl;
    std::cout << "Capacity: " << i.capacity() << std::endl;

    /// Insert to size 0 with some capacity
    i.reserve(2);
    i.resize(0);
    it = i.insert(i.begin(), 5);
    printVector<int>(i);
    std::cout << "Return: " << *it << std::endl;
    std::cout << "Size: " << i.size() << std::endl;
    std::cout << "Capacity: " << i.capacity() << std::endl;

    /// Insert exceed size && capacity
    for (int j = 0; j < 5; j++)
    {
        it = i.insert(i.begin(), j);
        printVector<int>(i);
        std::cout << "Return: " << *it << std::endl;
        std::cout << "Size: " << i.size() << std::endl;
        std::cout << "Capacity: " << i.capacity() << std::endl;
    }
    for (int j = 0; j < 5; j++)
    {
        it = i.insert(i.end(), j);
        printVector<int>(i);
        std::cout << "Return: " << *it << std::endl;
        std::cout << "Size: " << i.size() << std::endl;
        std::cout << "Capacity: " << i.capacity() << std::endl;
    }
    for (int j = 0; j < 10; j++)
    {
        it = i.insert(i.begin() + j, j);
        printVector<int>(i);
        std::cout << "Return: " << *it << std::endl;
        std::cout << "Size: " << i.size() << std::endl;
        std::cout << "Capacity: " << i.capacity() << std::endl;
    }

    /// Random Insert
    vector<int> r(42, 42);
    for (int i = 0; i < 20; i++)
    {
        it = r.insert(r.begin() + i, i);
        printVector<int>(r);
        std::cout << "Return: " << *it << std::endl;
        std::cout << "Size: " << r.size() << std::endl;
        std::cout << "Capacity: " << r.capacity() << std::endl;
    }
    tail();

    /**
     *  @brief Fill insert
     */
    head("Fill insert");
    /// Insert to 0 capacity
    vector<int> f;
    f.insert(f.begin(), 10, 42);
    printVector<int>(f);
    std::cout << "Size: " << f.size() << std::endl;

    /// Insert to start
    f.insert(f.begin(), 5, 41);
    printVector<int>(f);
    std::cout << "Size: " << f.size() << std::endl;

    /// Insert to end
    f.insert(f.end(), 9, 43);
    printVector<int>(f);
    std::cout << "Size: " << f.size() << std::endl;

    /// Insert with 0 n
    f.insert(f.begin() + 10, 0, 45);
    printVector<int>(f);
    std::cout << "Size: " << f.size() << std::endl;

    /// Insert with 1 n
    f.insert(f.begin() + 10, 1, 45);
    printVector<int>(f);
    std::cout << "Size: " << f.size() << std::endl;

    /// Insert with 5 n
    f.insert(f.begin() + 5, 5, 0);
    printVector<int>(f);
    std::cout << "Size: " << f.size() << std::endl;

    /// Insert with random
    for (int i = 0; i < 20; i++)
    {
        f.insert(f.begin() + i, i, i);
        printVector<int>(f);
        std::cout << "Size: " << f.size() << std::endl;
    }
    tail();

    /**
     *  @brief Range insert
     */

    head("Range insert");

    /// Insert from empty at begin()
    vector<int> k;
    k.insert(k.begin(), f.begin(), f.end());
    printVector<int>(k);
    std::cout << "Size: " << k.size() << std::endl;

    /// Insert with first == last
    vector<int> k1;
    k1.insert(k1.begin(), f.begin(), f.begin());
    printVector<int>(k1);
    std::cout << "Size: " << k1.size() << std::endl;

    /// Insert with empty at end()
    vector<int> k2;
    k2.insert(k2.end(), f.begin(), f.end());
    printVector<int>(k2);
    std::cout << "Size: " << k2.size() << std::endl;

    /// Insert from an end()
    k.insert(k.end(), k2.begin(), k2.end());
    printVector<int>(k);
    std::cout << "Size: " << k.size() << std::endl;

    /// Insert from middle with size 1
    k.insert(k.begin() + 10, k2.begin(), k2.begin() + 1);
    printVector<int>(k);
    std::cout << "Size: " << k.size() << std::endl;

    /// Insert with 42 Size
    k.insert(k.begin() + 42, k2.begin(), k2.begin() + 42);
    printVector<int>(k);
    std::cout << "Size: " << k.size() << std::endl;
    tail();

    /**
     *  @brief Erase 1 element
     */
    head("Erase element");
    vector<int> one(1);
    it = one.erase(one.begin());
    printVector<int>(one);
    std::cout << "Size: " << one.size() << std::endl;

    vector<int> two(2, 2);
    it = two.erase(two.begin() + 1);
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;

    two.insert(two.begin(), 3);
    it = two.erase(two.begin() + 1);
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;

    for (int i = 0; i < 5; i++)
    {
        two.insert(two.begin(), i);
    }
    it = two.erase(two.end() - 1);
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;
    tail();

    /**
     *  @brief Erase range of element
     */
    head("Erase range");
    it = two.erase(two.begin(), two.end());
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;

    for (int i = 0; i < 20; i++)
    {
        two.insert(two.begin(), i);
    }
    it = two.erase(two.begin(), two.begin());
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;

    it = two.erase(two.begin(), two.begin() + 2);
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;

    it = two.erase(two.begin() + 2, two.begin() + 5);
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;

    it = two.erase(two.begin() + 2, two.end());
    printVector<int>(two);
    std::cout << "IT location: " << *it << std::endl;
    std::cout << "Size: " << two.size() << std::endl;
    tail();
    return (0);
}
