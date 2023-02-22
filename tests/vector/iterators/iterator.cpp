#include <iomanip>
#include <iostream>
#include <vector>
#include "../../../vector.hpp"

#ifdef FT
    using namespace ft;
#else
    using namespace std;
#endif

template<typename T>
void printVector(vector<T>& v)
{
    std::cout << "Vector: ";
    for (typename vector<T>::iterator it = v.begin(); it != v.end(); it++)
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
    vector<char> empty;
    vector<char> test;

    for (int i = 0; i < 20; i++)
    {
        test.push_back(48 + i);
    }
    /**
     *  @defgroup Test for iterator
     */
    head("Iterator");
    /// Test empty normal iterator
    printVector(empty);

    /// Test normal vector
    printVector(test);
    tail();

    head("Reverse Iterator");
    /// Test reverse empty
    for (vector<char>::reverse_iterator it = empty.rbegin(); it != empty.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    /// Test reverse vector
    for (vector<char>::reverse_iterator it = test.rbegin(); it != test.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    tail();

    /// Test relational operator
    vector<char>::iterator start = test.begin();
    vector<char>::iterator mid = test.begin() + 5;
    vector<char>::iterator end = test.end();
    vector<char>::reverse_iterator rstart = test.rbegin();
    vector<char>::reverse_iterator rmid = test.rbegin() + 1;
    vector<char>::reverse_iterator rend = test.rend();

    head("Operator==");
    // Test ==
    std::cout << "(start == start)" << (start == start) << std::endl;
    std::cout << "(start == mid)" << (start == mid) << std::endl;
    std::cout << "(rstart == rstart)" << (rstart == rstart) << std::endl;
    std::cout << "(rstart == rmid)" << (rstart == rmid) << std::endl;
    tail();

    head("Operator!=");
    // Test !=
    std::cout << "(start != start)" << (start != start) << std::endl;
    std::cout << "(start != mid)" << (start != mid) << std::endl;
    std::cout << "(rstart != rstart)" << (rstart != rstart) << std::endl;
    std::cout << "(rstart != rmid)" << (rstart != rmid) << std::endl;
    tail();

    head("Operator>");
    // Test >
    std::cout << "(start > start)" << (start > start) << std::endl;
    std::cout << "(start > mid)" << (start > mid) << std::endl;
    std::cout << "(end > mid)" << (end > mid) << std::endl;
    std::cout << "(rstart > rstart)" << (rstart > rstart) << std::endl;
    std::cout << "(rstart > rmid)" << (rstart > rmid) << std::endl;
    std::cout << "(rend > rmid)" << (rend > rmid) << std::endl;
    tail();

    head("Operator<");
    // Test <
    std::cout << "(start < start)" << (start < start) << std::endl;
    std::cout << "(start < mid)" << (start < mid) << std::endl;
    std::cout << "(end < mid)" << (end < mid) << std::endl;
    std::cout << "(rstart < rstart)" << (rstart < rstart) << std::endl;
    std::cout << "(rstart < rmid)" << (rstart < rmid) << std::endl;
    std::cout << "(rend < rmid)" << (rend < rmid) << std::endl;
    tail();

    head("Operator>=");
    // Test >=
    std::cout << "(start >= start)" << (start >= start) << std::endl;
    std::cout << "(start >= mid)" << (start >= mid) << std::endl;
    std::cout << "(end >= mid)" << (end >= mid) << std::endl;
    std::cout << "(rstart >= rstart)" << (rstart >= rstart) << std::endl;
    std::cout << "(rstart >= rmid)" << (rstart >= rmid) << std::endl;
    std::cout << "(rend >= rmid)" << (rend >= rmid) << std::endl;
    tail();

    head("Operator<=");
    // Test <=
    std::cout << "(start <= start)" << (start <= start) << std::endl;
    std::cout << "(start <= mid)" << (start <= mid) << std::endl;
    std::cout << "(end <= mid)" << (end <= mid) << std::endl;
    std::cout << "(rstart <= rstart)" << (rstart <= rstart) << std::endl;
    std::cout << "(rstart <= rmid)" << (rstart <= rmid) << std::endl;
    std::cout << "(rend <= rmid)" << (rend <= rmid) << std::endl;
    tail();

    head("Increment");
    // test increment
    for (vector<char>::iterator it = test.begin(); it != test.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (vector<char>::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    tail();

    head("Decrement");
    // test decrement
    for (vector<char>::iterator it = test.end(); it != test.begin();)
    {
        --it;
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (vector<char>::reverse_iterator it = test.rend(); it != test.rbegin();)
    {
        --it;
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    tail();

    head("Indexing");
    // test indexing
    std::cout << test.begin()[0] << std::endl;
    std::cout << test.begin()[5] << std::endl;
    std::cout << test.rbegin()[0] << std::endl;
    std::cout << test.rbegin()[5] << std::endl;
    tail();

    head("Arithmetic");
    // test arithmetic
    std::cout << *(test.begin() + 0) << std::endl;
    std::cout << *(test.begin() + 5) << std::endl;
    std::cout << *(test.end() - 1) << std::endl;
    std::cout << *(test.end() - 10) << std::endl;
    std::cout << *(test.rbegin() + 0) << std::endl;
    std::cout << *(test.rbegin() + 5) << std::endl;
    std::cout << *(test.rend() - 1) << std::endl;
    std::cout << *(test.rend() - 10) << std::endl;
    tail();
}
