#pragma once
#include <vector>
#include "OctreePoint.h"
using namespace std;

class Octree {
	Vec3 lowerLeftBack;
	Vec3 highRightFront;
	Octree* children[8];
	OctreePoint* data;
public:
	Octree(const Vec3& lowerLeftBack, const Vec3& highRightFront)
		: lowerLeftBack(lowerLeftBack), highRightFront(highRightFront), data(nullptr) {
		// Initially, there are no children
		for (int i = 0; i < 8; ++i)
			children[i] = nullptr;
	}

	Octree(const Octree& copy)
		: lowerLeftBack(copy.lowerLeftBack), highRightFront(copy.highRightFront), data(copy.data) {}

	~Octree() {
		for (int i = 0; i < 8; ++i)
			delete children[i];
	}

	int getOctantContainingPoint(const Vec3& point) const {
		int oct = 0;
		Vec3 origin = (highRightFront + lowerLeftBack) / 2;
		if (point.x >= origin.x) oct |= 4;
		if (point.y >= origin.y) oct |= 2;
		if (point.z >= origin.z) oct |= 1;
		return oct;
	}

	bool isLeafNode() const {
		return children[0] == nullptr;
	}

	void insert(OctreePoint* point) {
		//if (point->getPosition().x< lowerLeftBack.x|| point->getPosition().x > highRightFront.x || point->getPosition().y < lowerLeftBack.y || point->getPosition().y > highRightFront.y || point->getPosition().z < lowerLeftBack.z || point->getPosition().z > highRightFront.z) {
		//	cout << "insert failed! because the point is out of range"<< point->getPosition().x << point->getPosition().y << point->getPosition().z<< endl;
		//	cout << lowerLeftBack.x << lowerLeftBack.y << lowerLeftBack.z << endl;
		//	return;
		//}

		if (isLeafNode()) {
			// 当前节点为叶子节点且未存入信息则存入该点
			if (data == nullptr) {
				data = point;
				return;
			}
			// 在当前叶子节点的基础上拓展八个叶子节点，将原来的点信息和新的点信息存入新的叶子节点中
			else {
				if (data->getPosition() == point->getPosition()) {
					cout << "insert failed! because the point is already exist" << endl;
				}
				else {
					// cout << lowerLeftBack.x << " " << lowerLeftBack.y << " " << lowerLeftBack.z << " " << endl;
					OctreePoint* oldPoint = data;
					data = nullptr;
					Vec3 origin = (highRightFront + lowerLeftBack) / 2;
					Vec3 offsetX = Vec3(origin.x - lowerLeftBack.x,0, 0 );
					Vec3 offsetY = Vec3(0, origin.y - lowerLeftBack.y, 0 );
					Vec3 offsetZ = Vec3(0, 0, origin.z - lowerLeftBack.z);
					Vec3 Vec3Zero = Vec3(0, 0, 0);
					for (int i = 0; i < 8; ++i) {
						Vec3 newOffset = Vec3Zero;
						newOffset += i & 4 ? offsetX : Vec3Zero;
						newOffset += i & 2 ? offsetY : Vec3Zero;
						newOffset += i & 1 ? offsetZ : Vec3Zero;
						children[i] = new Octree(lowerLeftBack + newOffset, origin + newOffset);
					}
					children[getOctantContainingPoint(oldPoint->getPosition())]->insert(oldPoint);
					children[getOctantContainingPoint(point->getPosition())]->insert(point);
				}
			}
		}
		else {
			int octant = getOctantContainingPoint(point->getPosition());
			children[octant]->insert(point);
		}
	}

	void find(const Vec3& bmin, const Vec3& bmax, std::vector<OctreePoint*>& results) {
		if (isLeafNode()) {
			if (data != nullptr) {
				const Vec3& p = data->getPosition();
				if (p.x > bmax.x || p.y > bmax.y || p.z > bmax.z) return;
				if (p.x < bmin.x || p.y < bmin.y || p.z < bmin.z) return;

				results.push_back(data);
			}
		}
		else {
			for (int i = 0; i < 8; ++i) {
				Vec3 cmax = children[i]->highRightFront;
				Vec3 cmin = children[i]->lowerLeftBack;

				if (cmax.x < bmin.x || cmax.y < bmin.y || cmax.z < bmin.z) continue;
				if (cmin.x > bmax.x || cmin.y > bmax.y || cmin.z > bmax.z) continue;

				children[i]->find(bmin, bmax, results);
			}
		}
	}
};