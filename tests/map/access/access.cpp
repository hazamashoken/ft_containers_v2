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
    map<int, int>   first;

    head("Operator[]");
    first.insert(pair<int, int>(0, 42));
    first.insert(pair<int, int>(5, 47));
    first.insert(pair<int, int>(3, 42));
    first.insert(pair<int, int>(7, 43));
    printMap(first);
    std::cout << first[0] << std::endl;
    first[1];
    printMap(first);
    first[1] = 1;
    printMap(first);
    first[0] = 21;
    first[42] = 42;
    printMap(first);
    tail();

    head("Method at()");
    std::cout << first.at(0) << std::endl;
    std::cout << first.at(42) << std::endl;
    try
    {
        std::cout << first.at(99) << std::endl;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "std::out_of_range caught" << std::endl;
    }
    tail();

    head("Insert with operator[]");
    map<std::string, int>   second;
    second["one"] = 1;
    second["two"] = 2;

    printMap(second);
    tail();
}
