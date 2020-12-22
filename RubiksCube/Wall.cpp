#include "Wall.h"
#include <iostream>



Wall::Wall(glm::vec3 _axisOfRotate, int _dir,int* _globalDir,int _n) : axisOfRotate(_axisOfRotate), dir(_dir), globalDir(_globalDir), n(_n)
{
	wallOfCubes = new MyCube * *[_n];
	for (int i = 0; i < n;i++) {
		wallOfCubes[i] = new MyCube * [_n];
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
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			int tmp = wallOfCubes[i][j]->getID();
			wallOfCubes[i][j]->setID(wallOfCubes[j][i]->getID());
			wallOfCubes[j][i]->setID(tmp);
		}
	}
	if (dir*(*globalDir) == 1 ) {
		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n / 2; ++j) {
				int tmp = wallOfCubes[i][j]->getID();
				wallOfCubes[i][j]->setID(wallOfCubes[i][n-1-j]->getID());
				wallOfCubes[i][ n-1-j]->setID(tmp);
			}
		}
	}
	else {
		for (int i = 0; i < n/2; ++i) {
			for (int j = 0; j < n; ++j) {
				int tmp = wallOfCubes[i][j]->getID();
				wallOfCubes[i][j]->setID(wallOfCubes[-i+n-1][j]->getID());
				wallOfCubes[-i+n-1][j]->setID(tmp);
			}
		}
	}
	//printMat();

}
Wall::~Wall() 
{
	for (int i = 0; i < n; i++) {
		delete wallOfCubes[i] ;
	}
	delete wallOfCubes;
}