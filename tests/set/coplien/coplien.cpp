#include <iomanip>
#include <iostream>
#include <set>
#include "../../../set.hpp"

#ifdef FT
    using namespace ft;
#else
    using namespace std;
#endif

template <typename T, typename C, typename A>
void printSet(set<T, C, A> a)
{
    typedef typename set<T, C, A>::iterator    iterator;
    std::cout << "Empty: " << a.empty() << std::endl;
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Element: ";
    for (iterator it = a.begin(); it != a.end(); ++it)
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
    head("Default constructor");
    //Default with std::less
    set<int>   first;

    printSet(first);
    first.insert(42);
    first.insert(47);
    first.insert(42);
    first.insert(43);
    printSet(first);

    //Default with std::greater
    set<int, std::greater<int> > second;
    printSet(second);
    second.insert(42);
    second.insert(47);
    second.insert(42);
    second.insert(43);
    printSet(second);
    tail();

    // Range constructor
    head("Range constructor");
    set<int, std::greater<int> >   third(first.begin(), first.end());
    printSet(third);
    tail();

    // Copy constructor
    head("Copy constructor");
    set<int, std::greater<int> > fourth(second);
    printSet(fourth);
    // Test for deep copy
    fourth.insert(99);
    printSet(fourth);
    printSet(second);
    tail();

    // Assignment operator test
    head("Assignment operator");
    fourth = second;
    printSet(fourth);
    printSet(second);

    // Test for deep copy
    fourth.insert(99);
    printSet(fourth);
    printSet(second);
    tail();
}
