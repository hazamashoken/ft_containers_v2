#include <iomanip>
#include <iostream>
#include <map>
#include "../../../map.hpp"

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
    typedef map<std::string, int, std::greater<std::string> >::iterator                    iterator;
    typedef map<std::string, int, std::greater<std::string> >::const_iterator              const_iterator;
    typedef map<std::string, int, std::greater<std::string> >::reverse_iterator            reverse_iterator;
    typedef map<std::string, int, std::greater<std::string> >::const_reverse_iterator      const_reverse_iterator;

    map<std::string, int, std::greater<std::string> > first;

    // Test begin() end() pre-increment with empty map
    head("++Iterator empty");
    for (iterator it = first.begin(); it != first.end(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test begin() end() post-increment with empty map
    head("Iterator++ empty");
    for (iterator it = first.begin(); it != first.end(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-increment with empty map
    head("++Const iterator empty");
    for (const_iterator it = first.begin(); it != first.end(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-increment with empty map
    head("Const iterator++ empty");
    for (const_iterator it = first.begin(); it != first.end(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test begin() end() pre-decrement with empty map
    head("--Iterator empty");
    for (iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test begin() end() post-decrement with empty map
    head("Iterator-- empty");
    for (iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-decrement with empty map
    head("--Const iterator empty");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-decrement with empty map
    head("Const iterator-- empty");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-increment with empty map
    head("++Reverse iterator empty");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-increment with empty map
    head("Reverse iterator++ empty");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-increment with empty map
    head("++Const Reverse iterator empty");
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() post-increment with empty map
    head("Const Reverse iterator++ empty");
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-decrement with empty map
    head("--Reverse iterator empty");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-decrement with empty map
    head("Reverse iterator-- empty");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-decrement with empty map
    head("--Const Reverse iterator empty");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() post-decrement with empty map
    head("Const Reverse iterator-- empty");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    first.insert(pair<std::string, int>("one", 1));
    first.insert(pair<std::string, int>("five", 5));
    first.insert(pair<std::string, int>("two", 2));
    first.insert(pair<std::string, int>("seven", 7));
    first.insert(pair<std::string, int>("four", 4));
    first.insert(pair<std::string, int>("three", 3));
    first.insert(pair<std::string, int>("six", 6));

    // Test begin() end() pre-increment with contents map
    head("++Iterator contents");
    for (iterator it = first.begin(); it != first.end(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test begin() end() post-increment with contents map
    head("Iterator++ contents");
    for (iterator it = first.begin(); it != first.end(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-increment with contents map
    head("++Const iterator contents");
    for (const_iterator it = first.begin(); it != first.end(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-increment with contents map
    head("Const iterator++ contents");
    for (const_iterator it = first.begin(); it != first.end(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test begin() end() pre-decrement with contents map
    head("--Iterator contents");
    for (iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test begin() end() post-decrement with contents map
    head("Iterator-- contents");
    for (iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() pre-decrement with contents map
    head("--Const iterator contents");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const begin() end() post-decrement with contents map
    head("Const iterator-- contents");
    for (const_iterator it = first.end(); it != first.begin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-increment with contents map
    head("++Reverse iterator contents");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-increment with contents map
    head("Reverse iterator++ contents");
    for (reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-increment with contents map
    head("++Const Reverse iterator contents");
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() post-increment with contents map
    head("Const Reverse iterator++ contents");
    for (const_reverse_iterator it = first.rbegin(); it != first.rend(); it++)
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() pre-decrement with contents map
    head("--Reverse iterator contents");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test rbegin() rend() post-decrement with contents map
    head("Reverse iterator-- contents");
    for (reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() pre-decrement with contents map
    head("--Const Reverse iterator contents");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        --it;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();

    // Test const rbegin() rend() post-decrement with contents map
    head("Const Reverse iterator-- contents");
    for (const_reverse_iterator it = first.rend(); it != first.rbegin();)
    {
        it--;
        std::cout << "(" << it->first << ", " << (*it).second << ")" << " ";
    }
    std::cout << std::endl;
    tail();
}
