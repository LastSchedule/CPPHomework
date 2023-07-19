#pragma once
#include<iostream>
class CustomArray {
public:
	//CustomArray(int length);//�ɱ����鹹��ʱ��ָ����ʼ��С
	CustomArray();
	CustomArray(const CustomArray& arr);
	~CustomArray();
	const CustomArray& operator = (const CustomArray& arr);
	int& operator [](int index);
	void reserve(int i);//Ԥ�ȷ����ڴ�ռ�
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
