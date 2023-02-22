#include <iomanip>
#include <iostream>
#include <deque>
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
    std::deque<char> a;

    a.push_back('h');
    a.push_back('e');
    a.push_back('l');
    a.push_back('l');
    a.push_back('o');
    a.push_back(',');
    a.push_back(' ');
    a.push_back('4');
    a.push_back('2');
    a.push_back('B');
    a.push_back('k');
    a.push_back('K');
    a.push_back('.');

    typedef set<char>::iterator iterator;
    set<char> first;

    printSet(first);
    // Insert with value
    pair<iterator, bool> p;
    head("Insert with value");
    p = first.insert('o');
    if (p.second)
        std::cout << "Inserted: " << *p.first << std::endl;
    else
        std::cout << "Existed: " << *p.first << std::endl;
    printSet(first);
    p = first.insert('o');
    if (p.second)
        std::cout << "Inserted: " << *p.first << std::endl;
    else
        std::cout << "Existed: " << *p.first << std::endl;
    printSet(first);
    p = first.insert('p');
    if (p.second)
        std::cout << "Inserted: " << *p.first << std::endl;
    else
        std::cout << "Existed: " << *p.first << std::endl;
    printSet(first);
    tail();

    // Hint insert
    head("Hint insert");
    iterator it;
    it = first.insert(p.first, 'f');
    std::cout << "Value: " << *it << std::endl;
    printSet(first);
    it = first.insert(it, 'o');
    std::cout << "Value: " << *it << std::endl;
    printSet(first);
    it = first.insert(it, 'o');
    std::cout << "Value: " << *it << std::endl;
    printSet(first);
    it = first.insert(it, 'b');
    std::cout << "Value: " << *it << std::endl;
    printSet(first);
    it = first.insert(it, 'a');
    std::cout << "Value: " << *it << std::endl;
    printSet(first);
    it = first.insert(it, 'r');
    std::cout << "Value: " << *it << std::endl;
    printSet(first);
    tail();

    // Range insert
    head("Range insert");
    first.insert(a.begin(), a.begin());
    printSet(first);
    first.insert(a.begin(), a.end());
    printSet(first);
    tail();

    // Erase with position
    head("Position Erase");
    first.erase(it);
    printSet(first);
    first.erase(first.begin());
    printSet(first);
    first.erase(++(++first.begin()));
    printSet(first);
    tail();

    // Erase with key
    head("Key Erase");
    size_t cnt;
    cnt = first.erase('!');
    std::cout << "Erased " << cnt << " element(s)" << std::endl;
    printSet(first);
    cnt = first.erase('k');
    std::cout << "Erased " << cnt << " element(s)" << std::endl;
    printSet(first);
    cnt = first.erase('k');
    std::cout << "Erased " << cnt << " element(s)" << std::endl;
    printSet(first);
    tail();

    // Erase range
    head("Range Erase");
    first.erase(first.begin(), first.begin());
    printSet(first);
    first.erase(first.begin(), ++first.begin());
    printSet(first);
    first.erase(--first.end(), first.end());
    printSet(first);
    first.erase(first.begin(), first.end());
    tail();

    // Swap test
    head("Swap");
    set<char> second(a.begin(), a.end());
    printSet(first);
    printSet(second);

    first.swap(second);
    printSet(first);
    printSet(second);
    tail();

    // Clear test
    head("Clear");
    first.clear();
    second.clear();
    printSet(first);
    printSet(second);
    tail();
}
