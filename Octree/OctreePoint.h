#pragma once

#include "Vec3.h"

class OctreePoint {
	Vec3  position;
public:
	OctreePoint() {}
	OctreePoint(const Vec3& _position):position(_position){}
	inline const Vec3& getPosition() const { return position; }
	inline void setPosition(const Vec3& p) { position = p; }
};