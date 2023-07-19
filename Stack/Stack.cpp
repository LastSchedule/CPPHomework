#pragma once
#include"iostream"
#include "Stack.h"
using namespace std;

template<typename T>
void StackInfo::push(const T& value) {
    _con.push_back(make_shared<InfoImpl<T>>(value));
}

template<typename T>
void StackInfo::pop(T& value) {
    auto item = dynamic_cast<InfoImpl<T>&>(*_con.back());
    value = item.getValue();
    _con.pop_back();
}

void test2()
{
    Test t1;

    StackInfo stack;  // 实现此类，就俩模板函数，push和pop
    stack.push(111);
    stack.push<std::string>("asdfasdfasdf");

    Test t2;
    t2.p3 = "t2teststring";
    stack.push(t2);
    stack.push(&t1);

    t1.testWithStack(stack);

    int ret = 0;
    stack.pop(ret);
    std::cout << "testWithStack ret " << ret << std::endl;
}

int main()
{
    test2();
    return 0;
}
