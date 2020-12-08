#include "Wall.h"
#include <iostream>



Wall::Wall(glm::vec3 _axisOfRotate, int _dir,int* _globalDir) : axisOfRotate(_axisOfRotate), dir(_dir), globalDir(_globalDir)
{
	wallOfCubes = new MyCube * *[3];
	for (int i = 0; i < 3;i++) {
		wallOfCubes[i] = new MyCube * [3];
	}
}

void Wall::printMat()
{
	printf(" Wall: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << " " << wallOfCubes[i][j]->getID();
		printf("\n");
	}
}


void Wall::setCubeAt(int i, int j, MyCube* cube)
{
	wallOfCubes[i][j] = cube;
}

void Wall::rotate()
{
	//printMat();
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < i; ++j) {
			int tmp = wallOfCubes[i][j]->getID();
			wallOfCubes[i][j]->setID(wallOfCubes[j][i]->getID());
			wallOfCubes[j][i]->setID(tmp);
		}
	}
	if (dir*(*globalDir) == 1 ) {
		
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3 / 2; ++j) {
				int tmp = wallOfCubes[i][j]->getID();
				wallOfCubes[i][j]->setID(wallOfCubes[i][j + 2]->getID());
				wallOfCubes[i][j + 2]->setID(tmp);
			}
		}
	}
	else {
		for (int i = 0; i < 3/2; ++i) {
			for (int j = 0; j < 3; ++j) {
				int tmp = wallOfCubes[i][j]->getID();
				wallOfCubes[i][j]->setID(wallOfCubes[i+2][j]->getID());
				wallOfCubes[i+2][j]->setID(tmp);
			}
		}
	}
	//printMat();

}
