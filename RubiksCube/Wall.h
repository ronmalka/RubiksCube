#pragma once
#include <build\RubiksCube\MyCube.h>
#include "glm/glm.hpp"
class Wall
{
public:
	Wall(glm::vec3 _axisOfRotate,int _dir);
	void setCubeAt(int i,int j, MyCube* cube);
	MyCube*** getWall() { return wallOfCubes; };
	glm::vec3 getAxis() { return axisOfRotate; };
	int getDir() { return dir; };
	void rotate();
	void printMat();
private:
	MyCube*** wallOfCubes;
	glm::vec3 axisOfRotate;
	int dir;
};

