#include <iomanip>
#include <iostream>
#include <list>
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
    std::list< pair<int, std::string> > lst;

    lst.push_back(pair<int, std::string>(5, "five"));
    lst.push_back(pair<int, std::string>(9, "nine"));
    lst.push_back(pair<int, std::string>(6, "six"));
    lst.push_back(pair<int, std::string>(3, "three"));
    lst.push_back(pair<int, std::string>(7, "seven"));
    lst.push_back(pair<int, std::string>(8, "eight"));
    lst.push_back(pair<int, std::string>(1, "one"));
    lst.push_back(pair<int, std::string>(2, "two"));
    lst.push_back(pair<int, std::string>(4, "four"));

    typedef map< int, std::string, std::greater<int> >::iterator    iterator;
    map< int, std::string, std::greater<int> >  empty;
    map< int, std::string, std::greater<int> >  first;

    iterator it;
    head("Find");
    // Find on empty map
    it = first.find(0);
    if (it == first.end())
        std::cout << "Key not found" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    it = first.find(5);
    if (it == first.end())
        std::cout << "Key not found" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;

    // Find on contents map
    first.insert(lst.begin(), lst.end());
    it = first.find(0);
    if (it == first.end())
        std::cout << "Key not found" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    it = first.find(5);
    if (it == first.end())
        std::cout << "Key not found" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    tail();

    size_t cnt;

    head("Count");

    // Count on empty map
    cnt = empty.count(0);
    std::cout << "Count: " << cnt << std::endl;
    cnt = empty.count(5);
    std::cout << "Count: " << cnt << std::endl;

    // Count in content map
    cnt = first.count(0);
    std::cout << "Count: " << cnt << std::endl;
    cnt = first.count(5);
    std::cout << "Count: " << cnt << std::endl;

    tail();

    head("Lower bound");
    // Lower bound in empty
    it = empty.lower_bound(5);
    if (it == empty.end())
        std::cout << "end() return" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;

    // Lower bound in contents map
    for (int i = -10; i < 15; ++i)
    {
        it = first.lower_bound(i);
        if (it == first.end())
            std::cout << "end() return" << std::endl;
        else
            std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    tail();

    head("Upper bound");
    // Upper bound in empty
    it = empty.upper_bound(5);
    if (it == empty.end())
        std::cout << "end() return" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;

    // Upper bound in contents map
    for (int i = -10; i < 15; ++i)
    {
        it = first.upper_bound(i);
        if (it == first.end())
            std::cout << "end() return" << std::endl;
        else
            std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    tail();

    // Equal range
    pair<iterator, iterator> p;

    head("Equal range");
    p = empty.equal_range(5);
    it = p.first;
    if (it == empty.end())
        std::cout << "end() return" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    it = p.second;
    if (it == empty.end())
        std::cout << "end() return" << std::endl;
    else
        std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;

    for (int i = -10; i < 15; ++i)
    {
        p = first.equal_range(i);
        it = p.first;
        if (it == first.end())
            std::cout << "end() return" << std::endl;
        else
            std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
        it = p.second;
        if (it == first.end())
            std::cout << "end() return" << std::endl;
        else
            std::cout << "(" << it->first << ", " << it->second << ")" << std::endl;
    }
    tail();
}

