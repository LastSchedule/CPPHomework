#define _CRT_SECURE_NO_WARNINGS
#include "CustomString.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;

CustomString::CustomString(const char* another)
{
    if (!another)
    {
        this->_str = new char[1];
        *this->_str = '\0';
        this->_size = 0;
    }
    else
    {
        delete[] this->_str;
        //int index = 0;
        //while (another[index] != '\0') {
        //    index++;
        //}
        //_size = index;
        this->_size = strlen(another);
        this->_str = new char[this->_size + 1];
        //strcpy(m_data, str);
        assert((this->_str != nullptr) && (another->_str != nullptr));
        char* temp = this->_str;
        while ((*temp++ = *another++) != '\0');
        this->_str[this->_size] = '\0';
    }
    //std::cout << "调用构造函数"<<std::endl;
}

CustomString::CustomString(const CustomString& another)
{
    int index = 0;
    if (another._size > 0) {
        while (another._str[index] != '\0') {
            index++;
        }
    }
    this->_size = index;
    this->_str = new char[_size + 1];
    //strcpy(_str, another._str);
    assert((this->_str != nullptr) && (another._str != nullptr));
    char* r = this->_str;
    char* temp = another._str;
    if (another._size > 0)
        while ((*r++ = *temp++) != '\0');
    //printf("%s", another._str);
    //std::cout << "调用拷贝构造函数"<<std::endl;
}

CustomString::~CustomString()
{
    delete[]  _str;
    //cout << "调用析构函数" << endl;
}

CustomString& CustomString::operator=(const char* another)
{
    delete[]  this->_str;
    this->_size = strlen(another);
    this->_str = new char[this->_size + 1];
    assert((_str != nullptr) && (another != nullptr));
    char* r = _str;
    if (strlen(another) > 0)
        while ((*r++ = *another++) != '\0');
    this->_str[this->_size] = '\0';
    return *this;
}

CustomString& CustomString::operator=(const CustomString& another)
{
    if (this != &another)
    {
        delete[] _str;    //释放原有内存
        if (!another._str)
        {
            _str = nullptr;
            _size = 0;
        }
        else
        {
            int index = 0;
            if (another._size > 0) {
                while (another._str[index] != '\0') {
                    index++;
                }
            }
            _size = index;
            _str = new char[_size + 1];
            //strcpy(_str, another._str);
            assert((_str != nullptr) && (another._str != nullptr));
            char* r = _str;
            char* temp = another._str;
            if (another._size > 0)
                while ((*r++ = *temp++) != '\0');
            this->_str[this->_size] = '\0';
        }
    }
    return *this;
}

bool CustomString::operator==(const CustomString& another)
{
    char* temp1 = _str;
    char* temp2 = another._str;
    while (*temp1 && *temp2 && *temp1++ == *temp2++);
    return *temp1 == *temp2;
}

int CustomString::len()
{
    return _size;
}

CustomString CustomString::sub(int index, int length)
{
    //delete[] _str;
    if (index > this->_size - 1) {
        cout << "sub所选起始下标不合法" << endl;
        return nullptr;
    }
    if (index + length > this->_size) {
        cout << "sub所选截取长度不合法" << endl;
        return nullptr;
    }

    int last_index = std::min(index + length, _size) - 1;//length越界应该警告，已弃用
    int new_size = last_index - index + 1;
    char* new_str = new char[new_size + 1];
    for (int i = index, j = 0; i <= last_index; i++, j++)
    {
        new_str[j] = _str[i];
    }
    new_str[new_size] = '\0';
    return new_str;
}

CustomString& CustomString::append(const char* another)
{
    int index = 0;
    while (another[index] != '\0') {
        index++;
    }
    int new_size = _size + index;
    char* new_str = new char[new_size + 1];
    char* temp = new_str;
    while ((*temp++ = *_str++) != '\0');
    temp--;
    while ((*temp++ = *another++) != '\0');
    //delete[] _str;//这里中断,会有内存碎片吗？
    _str = std::move(new_str);
    _size = new_size;
    return *this;
}

//KMP
void Next(const char* T, int* next) {
    int i = 1;
    next[1] = 0;
    int j = 0;
    while (i < strlen(T)) {
        if (j == 0 || T[i - 1] == T[j - 1]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

int CustomString::find(const char* another, int _index)
{
    int index = 0;
    while (another[index] != '\0') {
        index++;
    }
    int new_size = index;
    int next[10];
    Next(another, next);//根据模式串another,初始化next数组
    int i = _index + 1;
    int j = 1;
    while (i <= _size && j <= new_size) {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；_str[i-1]==another[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j == 0 || _str[i - 1] == another[j - 1]) {
            i++;
            j++;
        }
        else {
            j = next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j > new_size) {//如果条件为真，说明匹配成功
        return i - new_size - 1;
    }
    return -1;
}

//以下构造和拷贝构造调用次数为在待分割字符串为"test1,test2,test3"时
CustomString* CustomString::split(const char* another)
{
    std::vector<CustomString> elems;
    int another_len = 0;
    int another_num = 0;
    while (another[another_len] != '\0') {
        another_len++;
    }
    //char* pos_str = _str;//暂存_str起点，已弃用
    int index = 0;
    if (this->find(another, 0) == 0) {
        index = another_len;//特殊处理模式串在最前的情况
    }
    int last_index = this->find(another, index);//下标从index其找到待查找字符串的起始下标
    int length = last_index - index;//待截取的字符串长度
    if (length > 0) {//排除两个模式串间为空的情况
        CustomString sub1 = this->sub(index, length);//调用一次构造函数
        elems.push_back(sub1);//调用一次拷贝构造函数
    }
    //cout << "Vector Capacity:" << elems.capacity() << endl;
    while (last_index != -1) {
        //index = std::min(last_index + another_len, this->_size - 1);//下标不能越位
        index = last_index + another_len;
        //_str = _str + last_index + another_len;//之前想通过变_str改变find的起始位置，发现行不通，已弃用
        last_index = this->find(another, index);
        if (last_index != -1) {
            int length = last_index - index;
            if (length > 0) {
                CustomString sub1 = this->sub(index, length);//调用一次构造函数
                elems.push_back(sub1);//调用两次拷贝构造函数，依次拷贝test2,test1
            }
        }
        else {
            int length = this->_size - index;
            if (length > 0) {//排除','在最后的情况
                CustomString sub1 = this->sub(index, length);//调用一次构造函数
                elems.push_back(sub1);//调用三次拷贝构造函数，依次拷贝test3,test1，test2
            }
            //拷贝test3时发现vector空间不足(此时为2)的时候，重新分配一个大小为原来1.5倍的新空间，将旧空间的元素先拷贝到新空间后再将test3拷贝到新空间
            //为什么调用拷贝构造函数的时候会先输出test3呢
        }
        //cout << "Vector Capacity:" << elems.capacity() << endl;
    }
    CustomString* split_str = new CustomString[elems.size() + 1];//调用四次构造函数
    for (int i = 0; i < elems.size(); i++) {
        split_str[i] = elems[i];//被警告了额
        //elems[i].print_str();
    }

    split_str->_size = elems.size();
    return split_str;
    return nullptr;
}

int main() {
    auto str1 = CustomString("test1");
    str1 = "test3";
    cout << "str1: ";
    str1.print_str();
    auto str2 = CustomString("test2, test3");
    int len = str1.len();
    cout << "str1.len: " << len << endl;
    CustomString sub1 = str1.sub(1, 2);
    cout << "sub1: ";
    sub1.print_str();
    str1.append("append");
    bool equal = str1 == str2;
    cout << "str1: ";
    str1.print_str();
    cout << "str2: ";
    str2.print_str();
    int index = str1.find("es");
    cout << "Find es in str1: " << index << endl;
    auto str3 = CustomString(",test1,,test2,,test3,");//调用一次构造函数
    CustomString* ret = str3.split(",");//按','分割
    for (int i = 0; i < ret->len(); i++) {
        ret[i].print_str();
    }
    CustomString* ret2 = str3.split(",,");//按',,'分割
    for (int i = 0; i < ret2->len(); i++) {
        ret2[i].print_str();
    }
}
