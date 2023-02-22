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
    map< int, std::string, std::greater<int> >  first;

    head("Insert value");
    pair<iterator, bool> status = first.insert(pair<int, std::string>(0, "zero"));
    if (status.second)
    {
            std::cout << "Inserted: ";
            std::cout << "(" << status.first->first << ", " << status.first->second << ")" << std::endl;
    }
    else
    {
        std::cout << "Fail to insert duplicate key" << std::endl;
        std::cout << "Exist Value: ";
        std::cout << "(" << status.first->first << ", " << status.first->second << ")" << std::endl;
    }
    printMap(first);

    status = first.insert(pair<int, std::string>(0, "Not Zero"));
    if (status.second)
    {
            std::cout << "Inserted: ";
            std::cout << "(" << status.first->first << ", " << status.first->second << ")" << std::endl;
    }
    else
    {
        std::cout << "Fail to insert duplicate key" << std::endl;
        std::cout << "Exist Value: ";
        std::cout << "(" << status.first->first << ", " << status.first->second << ")" << std::endl;
    }
    printMap(first);
    tail();

    /// Hint insert
    head("Hint Insert");
    iterator ret = first.insert(status.first, pair<int, std::string>(99, "Ninety Nine"));
    std::cout << "Value: ";
    std::cout << "(" << ret->first << ", " << ret->second << ")" << std::endl;
    printMap(first);

    ret = first.insert(status.first, pair<int, std::string>(-1, "Negative one"));
    std::cout << "Value: ";
    std::cout << "(" << ret->first << ", " << ret->second << ")" << std::endl;
    printMap(first);

    ret = first.insert(ret, pair<int, std::string>(-1, "Positive one"));
    std::cout << "Value: ";
    std::cout << "(" << ret->first << ", " << ret->second << ")" << std::endl;
    printMap(first);
    tail();

    /// Range insert
    head("Range Insert");
    first.insert(lst.rbegin(), lst.rbegin());
    printMap(first);
    first.insert(lst.rbegin(), lst.rend());
    printMap(first);
    tail();

    /// Erase at position
    head("Erase at Position");
    first.erase(--first.end());
    printMap(first);
    first.erase(++(++(++(first.begin()))));
    printMap(first);
    tail();

    /// Erase with key
    head("Erase with key");
    size_t e_size = first.erase(99);
    std::cout << "Erase " << e_size << " element(s)" << std::endl;
    printMap(first);
    e_size = first.erase(99);
    std::cout << "Erase " << e_size << " element(s)" << std::endl;
    printMap(first);
    e_size = first.erase(42);
    std::cout << "Erase " << e_size << " element(s)" << std::endl;
    printMap(first);
    tail();

    /// Erase with iterator
    head("Erase range");
    first.erase(first.begin(), first.begin());
    printMap(first);
    first.erase(first.begin(), ++(++first.begin()));
    printMap(first);
    first.erase(--(--(--first.end())), --(--first.end()));
    printMap(first);
    first.erase(first.begin(), first.end());
    printMap(first);
    tail();

    first.insert(lst.begin(), lst.end());

    map< int, std::string, std::greater<int> >  second;
    map< int, std::string, std::greater<int> >  third;

    second[42] = "42 Bangkok";

    /// Call swap
    head("Swap");
    first.swap(second);

    printMap(first);
    printMap(second);

    first.swap(third);
    printMap(first);
    printMap(third);

    first.clear();
    second.clear();
    third.clear();

    printMap(first);
    printMap(second);
    printMap(third);
    tail();
}
