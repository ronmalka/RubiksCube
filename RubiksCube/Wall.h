#pragma once
#include "MyCube.h"
#include "glm/glm.hpp"
class Wall
{
public:
	Wall(glm::vec3 _axisOfRotate,int _dir,int* _globalDir,int _n);
	void setCubeAt(int i,int j, MyCube* cube);
	MyCube*** getWall() { return wallOfCubes; };
	glm::vec3 getAxis() { return axisOfRotate; };
	int getDir() { return dir; };
	void rotate();
	void printMat();
	void swap(MyCube* c1, MyCube* c2);
	~Wall();
private:
	MyCube*** wallOfCubes;
	glm::vec3 axisOfRotate;
	int dir;
	int* globalDir;
	int n;
};

