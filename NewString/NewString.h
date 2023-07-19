#pragma once

#include <stdio.h>
class CustomString {
public:
	CustomString(const char* str = nullptr);
	CustomString(const CustomString& other);
	~CustomString();
	CustomString& operator =(const char* another);
	CustomString& operator =(const CustomString& another);
	bool operator ==(const CustomString& another);
	int len();
	CustomString sub(int index, int length);
	CustomString& append(const char* str = nullptr);
	int find(const char* str = nullptr, int i = 0);
	CustomString* split(const char* another);
	void print_str() {
		printf("%s ", _str);
	}
private:
	char* _str;
	int _size;
};