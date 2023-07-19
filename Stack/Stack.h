#pragma once
#include<iostream>
#include <deque>
#include <memory>
using namespace std;

class Info {
public:
    virtual ~Info() {}
};

template<typename T>
class InfoImpl : public Info {
public:
    InfoImpl(T value) : _value(value) {}
    T& getValue() { return _value; }

private:
    T _value;
};

class StackInfo {
public:
    template<typename T>
    void push(const T& value);

    template<typename T>
    void pop(T& value);

private:
    deque<shared_ptr<Info>> _con;
    template<typename T>
    void pop(const T& value);
};

class Test
{
public:
    int p1 = 1;
    bool p2 = false;
    std::string p3 = "p33333333";

    void testWithStack(StackInfo& stack)
    {
        int v1 = 0;
        std::string v2;
        Test v3;
        Test* v4 = nullptr;

        stack.pop<Test*>(v4);
        stack.pop(v3);
        stack.pop(v2);
        stack.pop(v1);

        std::cout << "testWithStack "
            << v1 << " "
            << v2 << " "
            << v3.p3 << " "
            << v4->p3 << std::endl;

        stack.push(1);
    }
};