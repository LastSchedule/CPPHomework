#include "RingBuffer.h"
#include<iostream>
#include <string.h>
#include <algorithm>
using namespace std;

template <class T>
RingBuffer<T>::RingBuffer(int _size):capacity(_size),in(0),out(0) {
	pBuffer = new T[_size];
}

template <class T>
RingBuffer<T>::~RingBuffer() {
	delete []pBuffer;
    pBuffer = nullptr;
}

template <class T>
unsigned int RingBuffer<T>::size() {
	return (out - in + capacity) % capacity;
}

template <class T>
void RingBuffer<T>::Expend() {
	unsigned int newCapacity = 2 * capacity;
	T* newBuffer = new T[newCapacity];
	memcpy(newBuffer, pBuffer, capacity);
	delete[]pBuffer;
	pBuffer = newBuffer;
	capacity = newCapacity;
	cout << "Expend" <<endl;
}

template <class T>
void RingBuffer<T>::CheckShrink() {
	unsigned int newCapacity = 0.25f * capacity;
	if (size() > newCapacity) {
		return; // 如果目前的元素超过原容量的四分之一则不缩小
	}
	
	T* newBuffer = new T[capacity];
	if (in < out) {
		memcpy(newBuffer,pBuffer+in,out - in);
	}
	else {
		memcpy(newBuffer, pBuffer + out, capacity - out);
		memcpy(newBuffer, pBuffer, in);
	}
	out = size();
	in = 0;
	capacity = newCapacity * 2;
	delete []pBuffer;
	pBuffer = newBuffer;
	cout << "Shrink"<< endl;
}

template <class T>
void RingBuffer<T>::Write(const T value)
{
	if (in == (out + 1) % capacity) {
		Expend();
	}
	pBuffer[out] = value;
	out = (out + 1) % capacity;
}

template <class T>
void RingBuffer<T>::Write(const T* array)
{
	cout << "strlen(array)" << strlen(array)<<endl;
	if ((capacity-size()) < strlen(array)) {
		Expend();
	}
	for (int i = 0; i < strlen(array); i++) {
		pBuffer[out] = array[i];
		out = (out + 1) % capacity;
	}
}

template <class T>
void RingBuffer<T>::Read(const int count) {
	if (size()<count) {
		cout << "there are not enough elem" << endl;
		return;
	}
	in = (in + count) % capacity;
	CheckShrink();
}

template <class T>
void RingBuffer<T>::Traverse() {
	cout << "capacity: " << capacity<<" in: "<<in<<" out: "<<out << endl;
	if (in < out) {
		for (int i = in; i < out; i++) {
			cout << pBuffer[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = in;i<capacity;i++){
		cout << pBuffer[i] << " ";	
	}
	for (int i = 0; i < out; i++) {
		cout << pBuffer[i] << " ";
	}
	cout << endl;
}

int main()
{
	int initSize = 16;
	const char* data = "123456789";
	auto buffer = new RingBuffer<char>(initSize);
	buffer->Write(data);
	buffer->Read(6);
	buffer->Traverse();
	buffer->Write("abcdefgh");
	buffer->Traverse();
}
