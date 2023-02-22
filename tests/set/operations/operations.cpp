#include <iomanip>
#include <iostream>
#include <vector>
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
    std::vector<char> v;

    v.push_back('h');
    v.push_back('e');
    v.push_back('l');
    v.push_back('l');
    v.push_back('o');
    v.push_back(',');
    v.push_back(' ');
    v.push_back('4');
    v.push_back('2');
    v.push_back('B');
    v.push_back('k');
    v.push_back('K');
    v.push_back('.');

    set<char, std::greater<char> > empty;
    set<char, std::greater<char> > first(v.begin(), v.end());

    typedef set<char, std::greater<char> >::iterator    iterator;
    iterator it;

    // Find on empty
    head("Find on empty");
    it = empty.find('!');
    if (it == empty.end())
        std::cout << "return: end()" << std::endl;
    else
        std::cout << "return: " << *it << std::endl;
    tail();

    // Find on contents set
    head("Find on contents set");
    it = first.find('!');
    if (it == first.end())
        std::cout << "return: end()" << std::endl;
    else
        std::cout << "return: " << *it << std::endl;
    it = first.find('4');
    if (it == first.end())
        std::cout << "return: end()" << std::endl;
    else
        std::cout << "return: " << *it << std::endl;
    it = first.find('2');
    if (it == first.end())
        std::cout << "return: end()" << std::endl;
    else
        std::cout << "return: " << *it << std::endl;
    tail();

    // Count on empty
    head("Count on empty");
    size_t cnt;
    cnt = empty.count('!');
    std::cout << "Count: " << cnt << std::endl;
    cnt = empty.count('4');
    std::cout << "Count: " << cnt << std::endl;
    tail();

    // Count on contents
    head("Count on contents set");
    cnt = first.count('!');
    std::cout << "Count: " << cnt << std::endl;
    cnt = first.count('4');
    std::cout << "Count: " << cnt << std::endl;
    tail();

    // Lower bound on empty
    head("Lower bound on empty");
    for (char c = 'a'; c <= 'z'; ++c)
    {
        it = empty.lower_bound(c);
        if (it == empty.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
    }
    tail();

    // Lower bound on contents set
    head("Lower bound on contents set");
    for (char c = 'a'; c <= 'z'; ++c)
    {
        it = first.lower_bound(c);
        if (it == first.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
    }
    tail();

    // Upper bound on empty
    head("Upper bound on empty");
    for (char c = 'a'; c <= 'z'; ++c)
    {
        it = empty.upper_bound(c);
        if (it == empty.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
    }
    tail();

    // Upper bound on contents set
    head("Upper bound on contents set");
    for (char c = 'a'; c <= 'z'; ++c)
    {
        it = first.upper_bound(c);
        if (it == first.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
    }
    tail();

    pair<iterator, iterator> p;
    // Equal range on empty
    head("Equal range on empty");
    for (char c = 'a'; c <= 'z'; ++c)
    {
        p = empty.equal_range(c);
        it = p.first;
        if (it == empty.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
        it = p.second;
        if (it == empty.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
    }
    tail();

    // Equal range on contents set
    head("Equal range on contents set");
    for (char c = 'a'; c <= 'z'; ++c)
    {
        p = first.equal_range(c);
        it = p.first;
        if (it == first.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
        it = p.second;
        if (it == first.end())
            std::cout << "return: end()" << std::endl;
        else
            std::cout << "return: " << *it << std::endl;
    }
    tail();
}
