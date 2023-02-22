#include <iomanip>
#include <iostream>
#include <set>
#include "../../../set.hpp"

#ifdef FT
    using namespace ft;
#else
    using namespace std;
#endif

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
    typedef set<std::string, std::greater<std::string> >::iterator                    iterator;
    typedef set<std::string, std::greater<std::string> >::const_iterator              const_iterator;
    typedef set<std::string, std::greater<std::string> >::reverse_iterator            reverse_iterator;
    typedef set<std::string, std::greater<std::string> >::const_reverse_iterator      const_reverse_iterator;

    set<std::string, std::greater<std::string> > first;

    // Test begin() end() pre-increment with empty map
    head("++Iterator empty");
    for (iterator it = first.begin(); it != first.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test begin() end() post-increment with empty map
    head("Iterator++ empty");
    for (iterator it = first.begin(); it != first.end(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-increment with empty map
    head("++Const iterator empty");
    for (const_iterator it = first.begin(); it != first.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-increment with empty map
    head("Const iterator++ empty");
    for (const_iterator it = first.begin(); it != first.end(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test begin() end() pre-decrement with empty map
    head("--Iterator empty");
    for (iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test begin() end() post-decrement with empty map
    head("Iterator-- empty");
    for (iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-decrement with empty map
    head("--Const iterator empty");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-decrement with empty map
    head("Const iterator-- empty");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-increment with empty map
    head("++Reverse empty");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-increment with empty map
    head("Reverse++ empty");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-increment with empty map
    head("++Const reverse empty");
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    head("Const++ reverse empty");
    // Test const rbegin() rend() post-increment with empty map
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-decrement with empty map
    head("--Reverse empty");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-decrement with empty map
    head("Reverse empty--");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-decrement with empty map
    head("--Const reverse empty");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin(); --it)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() post-decrement with empty map
    head("Const reverse-- empty");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    first.insert("one");
    first.insert("five");
    first.insert("two");
    first.insert("seven");
    first.insert("four");
    first.insert("three");
    first.insert("six");

    // Test begin() end() pre-increment with contents map
    head("++Iterator contents");
    for (iterator it = first.begin(); it != first.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test begin() end() post-increment with contents map
    head("Iterator++ contents");
    for (iterator it = first.begin(); it != first.end(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-increment with contents map
    head("++Const iterator contents");
    for (const_iterator it = first.begin(); it != first.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-increment with contents map
    head("Const iterator++ contents");
    for (const_iterator it = first.begin(); it != first.end(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test begin() end() pre-decrement with contents map
    head("--Iterator contents");
    for (iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test begin() end() post-decrement with contents map
    head("Iterator-- contents");
    for (iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-decrement with contents map
    head("--Const iterator contents");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-decrement with contents map
    head("Const iterator-- contents");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-increment with contents map
    head("++Reverse contents");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-increment with contents map
    head("Reverse++ contents");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-increment with contents map
    head("++Const reverse contents");
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    head("Const++ reverse contents");
    // Test const rbegin() rend() post-increment with contents map
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-decrement with contents map
    head("--Reverse contents");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-decrement with contents map
    head("Reverse contents--");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-decrement with contents map
    head("--Const reverse contents");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() post-decrement with contents map
    head("Const reverse-- contents");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    tail();
}
