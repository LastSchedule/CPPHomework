#include<iostream>
#include"Array.h"
#include <cassert>
using namespace std;

CustomArray::CustomArray():_ptr(nullptr),_size(0),_capacity(0)
{

}

CustomArray::CustomArray(const CustomArray& arr) :_ptr(nullptr), _size(0), _capacity(0)
{
	if (arr._capacity < 1) return;
	_size = arr._size;
	_capacity = arr._capacity;
	_ptr = new int[_capacity];
	for (int i = 0; i < _size; i++) {
		_ptr[i] = arr._ptr[i];
	}
}

CustomArray::~CustomArray()
{
	delete[] _ptr;
}

const CustomArray& CustomArray::operator = (const CustomArray& arr)
{
	if (this == &arr)
		return *this;

	int* temp = new int[arr._capacity];
	for (int i = 0; i < arr._size; i++) {
		temp[i] = arr._ptr[i];
	}
	delete[] _ptr;
	_ptr = temp;
	_size = arr._size;
	_capacity = arr._capacity;

	return *this;
}

int& CustomArray::operator [](int index)
{
	if (index < 0 || index >= _capacity) {
		cout << "[]���±�Ƿ�" << endl;
		//return ;
	}
	else
		return _ptr[index];
}

void CustomArray::reserve(int i)
{
	if (i > _capacity) {
		int* temp = new int[i];
		for (int i = 0; i < _size; i++) {
			temp[i] = _ptr[i];
		}
		delete[] _ptr;
		_ptr = temp;
		_capacity = i;
	}
}

void CustomArray::push(int num)
{
	if (_size < _capacity) {
		_ptr[_size] = num;
		_size = _size + 1;
	}
	else {//��Ҫ������
		_capacity = _capacity * 3 / 2;
		int* temp = new int[_capacity];
		for (int i = 0; i < _size; i++)
			temp[i] = _ptr[i];
		temp[_size] = num;
		delete[] _ptr;
		_ptr = temp;
		_size = _size + 1;
	}
}

void CustomArray::insert(int index,int num)
{
	if (_size < _capacity) {
		for (int i = _size ; i > index; i--) {
			_ptr[i] = _ptr[i - 1];
		}
		_ptr[index] = num;
		_size++;
	}
	else {
		_capacity = _capacity * 3 / 2;
		int* temp = new int[_capacity];
		for (int i = _size; i > index; i--) {
			temp[i] = _ptr[i - 1];
		}
		temp[index] = num;
		for (int i = index - 1; i > 0; i--) {
			temp[i] = _ptr[i - 1];
		}
		delete[] _ptr;
		_ptr = temp;
		_size = _size + 1;
	}
}

//�������Է�����STL��vector��ʵ����Щ���룬�������1,2,1,5,7,9,6��һ���飬STL��remove(1)����������2,5,7,9,6,9,6;������2,5,7,9,6,6,6
//����͵���ˣ���������಻��Ҫ���ڴ濽��
void CustomArray::remove(int value)//vector�е�remove�ǽ�����value��Ԫ��֮�������Ԫ��ǰ�ƣ�����������size
{
	int index = -1;
	index = findIndex(value, index+1);
	while (index != -1) {
		memmove(_ptr + index, _ptr + index + 1, sizeof(_ptr[0]) * (_size - index - 1));
		index = findIndex(value, index + 1);
	}
}

void CustomArray::pop()
{
	_size--;
	if (_size * 3 / 2 <= _capacity)//��С����
		_capacity = _capacity * 2 / 3;
}

void CustomArray::clear()//�ı��С�����ı�����
{
	_size = 0;
	delete[] _ptr;
	//_ptr = nullptr;
}

int CustomArray::findIndex(int value,int index=0)
{
	assert(index > -1 && index < _size);

	for (int i = index; i < _size; i++) {
		if (_ptr[i] == value)
			return i;
	}
	return -1;
}

void CustomArray::print_size()
{
	cout << _size << endl;
}

void CustomArray::print_capacity()
{
	cout << _capacity << endl;
}

int main()
{
	auto arr = new CustomArray();
	arr->reserve(4);
	arr->push(1);
	arr->push(2);
	//arr->push(1);
	//arr->push(5);
	//arr->push(7);
	//arr->push(9);
	//arr->push(6);
	arr->insert(1, 3);
	arr->remove(1);
	arr->pop();
	int index = arr->findIndex(1);
	cout << index << endl;
	arr->clear();
	//arr->print_size();
	//arr->print_capacity();
	arr->print_arr();
	return 0;
}
