#pragma once
#include<iostream>
class CustomArray {
public:
	//CustomArray(int length);//可变数组构造时不指定初始大小
	CustomArray();
	CustomArray(const CustomArray& arr);
	~CustomArray();
	const CustomArray& operator = (const CustomArray& arr);
	int& operator [](int index);
	void reserve(int i);//预先分配内存空间
	void push(int i);
	void insert(int index,int num);
	void remove(int index);
	void pop();
	void clear();
	int findIndex(int value,int index);
	void print_size();
	void print_capacity();
	void print_arr() {
		for (int i = 0; i < _size; i++) {
			std::cout << _ptr[i] << " ";
		}
		std::cout << std::endl;
	}
private:
	int _size;
	int _capacity;
	int* _ptr;
};
