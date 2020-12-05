#pragma once
#include "scene.h"

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
	~RubiksCube(void);
};

