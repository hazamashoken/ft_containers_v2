#include <iomanip>
#include <iostream>
#include <map>
#include "../../../map.hpp"

#ifdef FT
    using namespace ft;
#else
    using namespace std;
#endif

template <typename Key, typename T, typename C, typename A>
void printMap(map<Key, T, C, A> a)
{
    typedef typename map<Key, T, C, A>::iterator    iterator;
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Element: ";
    for (iterator it = a.begin(); it != a.end(); ++it)
    {
        std::cout << "(" << it->first << ", " << it->second << ")" << " ";
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
    //Default with std::less
    head("Default std::less");
    map<int, int>   first;

    printMap(first);
    first.insert(pair<int, int>(0, 42));
    first.insert(pair<int, int>(5, 47));
    first.insert(pair<int, int>(3, 42));
    first.insert(pair<int, int>(7, 43));
    printMap(first);
    tail();

    //Default with std::greater
    head("Default std::greater");
    map<int, int, std::greater<int> > second;
    printMap(second);
    second.insert(pair<int, int>(0, 42));
    second.insert(pair<int, int>(5, 47));
    second.insert(pair<int, int>(3, 42));
    second.insert(pair<int, int>(7, 43));
    printMap(second);
    tail();

    // Range constructor
    head("Range constructor");
    map<int, int>   third(first.begin(), first.end());
    printMap(third);
    tail();

    // Copy constructor
    head("Copy constructor");
    map<int, int, std::greater<int> > fourth(second);
    printMap(fourth);
    // Test for deep copy
    fourth.insert(pair<int, int>(9, 99));
    printMap(fourth);
    printMap(second);
    tail();

    // Assignment operator test
    head("Assignment operator");
    fourth = second;
    printMap(fourth);
    printMap(second);

    // Test for deep copy
    fourth.insert(pair<int, int>(9, 99));
    printMap(fourth);
    printMap(second);
    tail();
}
