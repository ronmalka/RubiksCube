#pragma once
class MyCube
{
public:
	MyCube(float x,float y,float z,int _id);
	inline void setX(float _x) { x = _x; }
	inline void setY(float _y) { y = _y; }
	inline void setZ(float _z) { z = _z; }
	inline void setID(int _id) { id = _id; }
	inline float getX() { return x; }
	inline float getY() { return y; }
	inline float getZ() { return z; }
	inline float getID() { return id; }
private:
	float x;
	float y;
	float z;
	int id;
};

