#pragma once
#include "scene.h"
#include "MyCube.h"
#include "Wall.h"

#define myRight 0
#define myLeft 1
#define U 2
#define D 3
#define B 4
#define F 5
#define CW -1
#define CCW 1

class RubiksCube : public Scene
{
public:
	
	RubiksCube(int _n);
	void Init();
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	
	unsigned int TextureDesine(int width, int height);
	//inline MyCube**** getRub() { return rubCube; };
	void switchRowCols(MyCube*** arr);
	void reverseRows(MyCube*** arr);
	inline void setPicked(int i) { pickedShape = i; };
	inline void setGlobalDir() { globalDir = -globalDir; };
	void decGlobalSpeed();
	void incGlobalSpeed();
	inline int getGlobalSpeed() { return globalSpeed; };
	inline Wall* getWall(int type) { return walls[type]; };
	inline int getN() { return n; }
	inline int getPickedShape() { return pickedShape; }
	void doRotate(int wall);
	void printMat();
	void calcRGB(int id);
	void printRGB();
	void WhenPicked();
	~RubiksCube(void);
private:
	//MyCube**** rubCube;
	int n;
	Wall** walls;
	int globalDir;
	float globalSpeed;

};

