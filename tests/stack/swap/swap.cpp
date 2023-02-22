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

template <typename T, typename C>
void printStack(stack<T, C> a)
{
    std::cout << "Size: " << a.size() << std::endl;
    std::cout << "Element: ";
    for (; !a.empty();)
    {
        std::cout << a.top() << " ";
        a.pop();
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
    stack<float, std::deque<float> > first;

    std::deque<float> d(42, 4.2);
    stack<float, std::deque<float> > second(d);

    head("Swap with empty");
    std::cout << "Before" << std::endl;
    printStack(first);
    printStack(second);

    /// Using member function
    first.swap(second);
    std::cout << "After" << std::endl;
    printStack(first);
    printStack(second);

    // Using non-member function
    swap(first, second);
    printStack(first);
    printStack(second);
    tail();

    std::deque<float> d2(21 , 2.1);
    stack<float, std::deque<float> > third(d2);
    head("Swap with non-empty");
    std::cout << "Before" << std::endl;
    printStack(second);
    printStack(third);

    /// Using member function
    second.swap(third);
    std::cout << "After" << std::endl;
    printStack(second);
    printStack(third);

    // Using non-member function
    swap(third, second);
    printStack(second);
    printStack(third);
    tail();

}
