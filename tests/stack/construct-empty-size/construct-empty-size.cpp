#include <iomanip>
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include "../../../stack.hpp"

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
    // Using vector as container
    head("Using vector");
    vector<int> v_empty;
    vector<int> v_test(42, 42);

    stack<int, vector<int> > first(v_empty);
    stack<int, vector<int> > second(v_test);

    std::cout << "Empty: " << first.empty() << std::endl;
    std::cout << "Size: " << first.size() << std::endl;

    std::cout << "Empty: " << second.empty() << std::endl;
    std::cout << "Top: " << second.top() << std::endl;
    std::cout << "Size: " << second.size() << std::endl;
    tail();

    // Using std::deque as container
    head("Using deque");
    std::deque<char> d_empty;
    std::deque<char> d_test(10, 'a');

    stack<char, std::deque<char> >  third(d_test);
    stack<char, std::deque<char> >  fourth(d_test);

    std::cout << "Empty: " << third.empty() << std::endl;
    std::cout << "Top: " << third.top() << std::endl;
    std::cout << "Size: " << third.size() << std::endl;

    std::cout << "Empty: " << fourth.empty() << std::endl;
    std::cout << "Size: " << fourth.size() << std::endl;
    tail();
}
