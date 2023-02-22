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

    head("Size, Empty");
    std::cout << first.empty() << std::endl;
    printMap(first);
    first.insert(pair<int, int>(0, 42));
    first.insert(pair<int, int>(5, 47));
    first.insert(pair<int, int>(3, 42));
    first.insert(pair<int, int>(7, 43));
    std::cout << first.empty() << std::endl;
    printMap(first);
    tail();
}
