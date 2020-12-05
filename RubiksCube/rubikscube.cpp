#include "rubikscube.h"
#include <iostream>
#include "GL/glew.h"

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

RubiksCube::RubiksCube() : Scene()
{
}

//RubiksCube::RubiksCube(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{ 	
//}

void RubiksCube::Init()
{		
	unsigned int texIDs[3] = { 0 , 1, 0};
	unsigned int slots[3] = { 0 , 1, 0 };
	
	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader2");
	//AddShader("../res/shaders/basicShader");
	
	//AddTexture("../res/textures/pal.png",1);
	AddTexture("../res/textures/plane.png", 2);
	//TextureDesine(800, 800);

	AddMaterial(texIDs,slots, 2);

	for (int i = 0; i < 27; i++)
	{
		AddShape(Cube, -1, TRIANGLES);
		SetShapeShader(i, 1);
		SetShapeMaterial(0, 0);
	
	}
	int pickCounter = 0;
	int loc [3] = { -2,0,2 };
	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				pickedShape = pickCounter;
				ShapeTransformation(xTranslate, loc[x]);
				ShapeTransformation(yTranslate, loc[y]);
				ShapeTransformation(zTranslate, loc[z]-2);
				pickCounter++;
				pickedShape = -1;
			}
		}

	}
	
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void RubiksCube::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	if (shapes[pickedShape]->GetMaterial() >= 0 && !materials.empty())
		BindMaterial(s, shapes[pickedShape]->GetMaterial());
	//textures[0]->Bind(0);
	s->Bind();
	if (shaderIndx != 2)
	{
		s->SetUniformMat4f("MVP", MVP);
		s->SetUniformMat4f("Normal", Model);
	}
	else
	{
		s->SetUniformMat4f("MVP", glm::mat4(1));
		s->SetUniformMat4f("Normal", glm::mat4(1));
	}
	s->SetUniform1i("sampler1", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(0));
	if(shaderIndx!=2)
		s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));

	s->Unbind();
}

void RubiksCube::WhenRotate()
{
}

void RubiksCube::WhenTranslate()
{
}

void RubiksCube::Motion()
{
	if(isActive)
	{
	}
}

unsigned int RubiksCube::TextureDesine(int width, int height)
{
	unsigned char* data = new unsigned char[width * height * 4];
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			data[(i * height + j) * 4] = (i + j) % 256;
			data[(i * height + j) * 4 + 1] = (i + j * 2) % 256;
			data[(i * height + j) * 4 + 2] = (i * 2 + j) % 256;
			data[(i * height + j) * 4 + 3] = (i * 3 + j) % 256;
		}
	}
	textures.push_back(new Texture(width, height));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //note GL_RED internal format, to save 
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
	return(textures.size() - 1);
}

RubiksCube::~RubiksCube(void)
{

}
