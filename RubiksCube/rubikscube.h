#pragma once
#include "scene.h"
#include "MyCube.h"
#include "Wall.h"

#define R 0
#define L 1
#define U 2
#define D 3
#define B 4
#define F 5
#define CW -1
#define CCW 1

class RubiksCube : public Scene
{
public:
	
	RubiksCube();
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
	inline void decGlobalSpeed() { globalSpeed = globalSpeed*3; };
	inline void incGlobalSpeed() { globalSpeed = globalSpeed/3; };
	inline int getGlobalSpeed() { return globalSpeed; };
	inline Wall* getWall(int type) { return walls[type]; };
	void doRotate(int wall);
	void printMat();
	~RubiksCube(void);
private:
	//MyCube**** rubCube;
	Wall** walls;
	int globalDir;
	float globalSpeed;
};

