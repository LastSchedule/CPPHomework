#define _CRT_SECURE_NO_WARNINGS
#include "NewString.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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
		this->_size = strlen(another);
		this->_str = new char[this->_size + 1];
		//strcpy(m_data, str);
		assert((this->_str != nullptr));
		char* temp = this->_str;
		while ((*temp++ = *another++) != '\0');
		this->_str[this->_size] = '\0';
	}
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
	assert((this->_str != nullptr) && (another._str != nullptr));
	char* r = this->_str;
	char* temp = another._str;
	if (another._size > 0)
		while ((*r++ = *temp++) != '\0');
}

CustomString::~CustomString()
{
	delete[]  _str;
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
		delete[] _str;    //�ͷ�ԭ���ڴ�
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
		cout << "sub ��ѡ��ʼ�±겻�Ϸ�" << endl;
		return nullptr;
	}
	if (index + length > this->_size) {
		cout << "sub ��ѡ��ȡ���Ȳ��Ϸ�" << endl;
		return nullptr;
	}

	int last_index = std::min(index + length, _size) - 1;
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
	//delete[] _str;//�����ж�,�����ڴ���Ƭ��
	_str = std::move(new_str);
	_size = new_size;
	return *this;
}

// KMP
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
	Next(another, next);//����ģʽ��another,��ʼ��next����
	int i = _index + 1;
	int j = 1;
	while (i <= _size && j <= new_size) {
		//j==0:����ģʽ���ĵ�һ���ַ��ͺ͵�ǰ���Ե��ַ�����ȣ�_str[i-1]==another[j-1],�����Ӧλ���ַ���ȣ���������£�ָ��ǰ���Ե�����ָ���±�i��j�������
		if (j == 0 || _str[i - 1] == another[j - 1]) {
			i++;
			j++;
		}
		else {
			j = next[j];//������Ե������ַ�����ȣ�i������j��Ϊ��ǰ�����ַ�����nextֵ
		}
	}
	if (j > new_size) {//�������Ϊ�棬˵��ƥ��ɹ�
		return i - new_size - 1;
	}
	return -1;
}

CustomString* CustomString::split(const char* another)
{
	std::vector<CustomString> elems;
	int another_len = 0;
	int another_num = 0;
	while (another[another_len] != '\0') {
		another_len++;
	}
	int index = 0;
	if (this->find(another, 0) == 0) {
		index = another_len;//���⴦��ģʽ������ǰ�����
	}
	int last_index = this->find(another, index);//�±��index���ҵ��������ַ�������ʼ�±�
	int length = last_index - index;//����ȡ���ַ�������
	if (length > 0) {//�ų�����ģʽ����Ϊ�յ����
		CustomString sub1 = this->sub(index, length);
		elems.push_back(sub1);
	}
	while (last_index != -1) {
		index = last_index + another_len;
		last_index = this->find(another, index);
		if (last_index != -1) {
			int length = last_index - index;
			if (length > 0) {
				CustomString sub1 = this->sub(index, length);
				elems.push_back(sub1);
			}
		}
		else {
			int length = this->_size - index;
			if (length > 0) {//�ų�','���������
				CustomString sub1 = this->sub(index, length);
				elems.push_back(sub1);
			}
		}
	}
	int size = elems.size();
	CustomString* split_str = new CustomString[size];
	for (int i = 0; i < size; i++) {
		split_str[i] = elems[i];
	}
	split_str->_size = size;
	return split_str;
}

int main() {
	auto str1 = CustomString("test1");
	auto str2 = CustomString("test2, test3");
	str1 = "test3";

	cout << "str1: ";
	str1.print_str();
	cout << endl;

	int len = str1.len();
	cout << "str1.len: " << len << endl;

	CustomString sub1 = str1.sub(1, 2);
	cout << "sub1: ";
	sub1.print_str();
	cout << endl;

	str1.append("append");
	cout << "append: ";
	str1.print_str();
	cout << endl;

	bool equal = str1 == str2;
	cout << "str1 == str2?: "<<equal<<endl;

	int index = str1.find("es");
	cout << "Find es in str1: " << index << endl;

	auto str3 = CustomString(",test1,,test2,,test3,");
	CustomString* ret = str3.split(",");//��','�ָ�
	for (int i = 0; i < ret->len(); i++) {
		ret[i].print_str();
	}
	cout << endl;
	CustomString* ret2 = str3.split(",,");//��',,'�ָ�
	for (int i = 0; i < ret2->len(); i++) {
		ret2[i].print_str();
	}
	cout << endl;
}
