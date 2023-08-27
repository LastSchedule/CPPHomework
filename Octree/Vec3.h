#pragma once

#include <iostream>
#include <cmath>

typedef float TYPE;

class Vec3 {
public:
	union
	{
		struct 
		{
			TYPE x, y, z;
		};
		TYPE pos[3];
	};
	

	Vec3() :pos{ -1,-1,-1 } {}
	Vec3(TYPE x, TYPE y, TYPE z) :pos{x, y, z}{}

	// 重载索引操作符
	TYPE& operator[](unsigned int i) { return pos[i]; }
	const TYPE operator[](unsigned int i) const { return pos[i]; }

	// 重载四则运算符
	Vec3 operator+(const Vec3& r) const {
		return Vec3(pos[0] + r[0], pos[1] + r[1], pos[2] + r[2]);
	}

	Vec3 operator-(const Vec3& r) const {
		return Vec3(pos[0] - r[0], pos[1] - r[1], pos[2] - r[2]);
	}

	Vec3 operator*(float r) const {
		return Vec3(pos[0] * r, pos[1] * r, pos[2] * r);
	}

	Vec3 operator/(float r) const {
		return Vec3(pos[0] / r, pos[1] / r, pos[2] / r);
	}

	// 重载复合赋值运算符
	Vec3& operator+=(const Vec3& r) {
		pos[0] += r[0];
		pos[1] += r[1];
		pos[2] += r[2];
		return *this;
	}

	Vec3& operator-=(const Vec3& r) {
		pos[0] -= r[0];
		pos[1] -= r[1];
		pos[2] -= r[2];
		return *this;
	}

	Vec3& operator*=(float r) {
		pos[0] *= r; pos[1] *= r; pos[2] *= r;
		return *this;
	}

	bool operator == (const Vec3 & r)const {
		return x == r.x && y == r.y && z == r.z;
	}
};