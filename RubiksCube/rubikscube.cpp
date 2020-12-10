#include "rubikscube.h"
#include <iostream>
#include "GL/glew.h"
#define Max_Sleep 10
#define Min_Sleep 0


void RubiksCube::printMat()
{
	printf(" Wall Right: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << " " << walls[myRight]->getWall()[i][j]->getID();
			
		printf("\n");
	}
	printf(" Wall UP: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << " " << walls[U]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall DOWN: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << " " << walls[D]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall LEFT: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << " " << walls[myLeft]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall BACK: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << " " << walls[B]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall FORWARD: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			std::cout << " " << walls[F]->getWall()[i][j]->getID();
		printf("\n");
	}
}

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

RubiksCube::RubiksCube(int _n) : Scene()
{
	n = _n; // CHANGE THIS TO SHOW THE BONUS!
	globalDir = 1;
	globalSpeed = Min_Sleep;
	walls = new Wall * [6];
	walls[myRight] = new Wall(glm::vec3(1.f,0.f ,0.f),CW,&globalDir,n);
	walls[myLeft] = new Wall(glm::vec3(-1.f, 0.f, 0.f), CW, &globalDir,n);
	walls[U] = new Wall(glm::vec3(0.f, 1.f, 0.f), CW, &globalDir,n);
	walls[D] = new Wall(glm::vec3(0.f, -1.f, 0.f), CW, &globalDir,n);
	walls[F] = new Wall(glm::vec3(0.f, 0.f, 1.f), CW, &globalDir,n);
	walls[B] = new Wall(glm::vec3(0.f, 0.f, -1.f),CW, &globalDir,n);

}

//RubiksCube::RubiksCube(float angle ,float relationWH, float near, float far) : Scene(angle,relationWH,near,far)
//{ 	
//}

void RubiksCube::Init()
{
	GLuint pickingColorID = glGetUniformLocation(pickedShape, "PickingColor");
	unsigned int texIDs[3] = { 0 , 1, 0};
	unsigned int slots[3] = { 0 , 1, 0 };
	
	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader2");
	//AddShader("../res/shaders/basicShader");
	
	//AddTexture("../res/textures/pal.png",1);
	AddTexture("../res/textures/plane.png", 2);
	//TextureDesine(800, 800);

	AddMaterial(texIDs,slots, 2);

	int pickCounter = 0;
	int loc [3] = { -2,0,2 };
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			for (int z = 0; z < n; z++)
			{
				AddShape(Cube, -1, TRIANGLES);
				SetShapeShader(pickCounter, 0);
				SetShapeShader(pickCounter, 1);
				SetShapeMaterial(0, 0);
				pickedShape = pickCounter;
				ShapeTransformation(xTranslate, -(n-1) + 2*x);
				ShapeTransformation(yTranslate, -(n-1) + 2*y);
				ShapeTransformation(zTranslate, -(n-1) +2*z);
				MyCube* c = new MyCube(-(n - 1) + 2 * x, -(n - 1) + 2 * y, -(n - 1) + 2 * z,pickCounter);
				if (x == 0) {
					walls[myLeft]->setCubeAt(y,z,c);
				}
				else if (x == n-1) {
					walls[myRight]->setCubeAt(y,n-1-z,c);
				}
				if (y==0) {
					walls[D]->setCubeAt(n-1-x,z,c);
				}
				else if (y == n-1) {
					walls[U]->setCubeAt(x,z,c);
				}
				if (z == 0) {
					walls[B]->setCubeAt(x,y,c);
				}
				else if (z == n-1) {
					walls[F]->setCubeAt(x,n-1-y,c);
				}
				pickCounter++;
				pickedShape = -1;
			}
		}

	}
	printRGB();
	
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void RubiksCube::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape) & 0x000000FF) >>  0;
	int g = ((pickedShape) & 0x0000FF00) >>  8;
	int b = ((pickedShape) & 0x00FF0000) >> 16;
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
	s->SetUniform4f("lightColor", r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	s->SetUniform1i("sampler1", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(0));
	if(shaderIndx!=2)
		s->SetUniform1i("sampler2", materials[shapes[pickedShape]->GetMaterial()]->GetSlot(1));

	s->Unbind();
}

void RubiksCube::WhenRotate()
{
	//MyRotate(-xrel / 2.0f, glm::vec3(0, 1, 0), 0);
	//MyRotate(-yrel / 2.0f, glm::vec3(1, 0, 0), 1);
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

void RubiksCube::switchRowCols(MyCube*** arr)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < i; ++j) {
			MyCube* tmp = arr[i][j];
			arr[i][j] = arr[j][i];
			arr[j][i] = tmp;
		}
	}
	for (int i = 0; i < 3 / 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			MyCube* tmp = arr[i][j];
			arr[i][j] = arr[i + 2][j];
			arr[i + 2][j] = tmp;
		}
	}
}

void RubiksCube::reverseRows(MyCube*** arr)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3 / 2; ++j) {
			MyCube* tmp = arr[i][j];
			arr[i][j] = arr[i][j + 2];
			arr[i][j + 2]= tmp;
		}
	}
}

void RubiksCube::doRotate(int wall)
{
	Wall* myWall = walls[wall];
	MyCube*** myCubes = myWall->getWall();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			MyCube* c = myCubes[i][j];
			pickedShape = c->getID();
			shapes[pickedShape]->RotateTranslate(myWall->getDir()*globalDir * 1.f, myWall->getAxis(), 0);
			pickedShape = -1;
		}
	}
	//walls[wall]->rotate();
}

void RubiksCube::decGlobalSpeed()
{
	globalSpeed = globalSpeed--;
	if (globalSpeed < Min_Sleep)
	{
		globalSpeed = Min_Sleep;
	}
}
void RubiksCube::incGlobalSpeed()
{
	globalSpeed = globalSpeed++;
	if (globalSpeed > Max_Sleep)
	{
		globalSpeed = Max_Sleep;
	}

}
void RubiksCube::calcRGB(int id) 
{
	int r = ((id) & 0x000000FF) >> 0;
	int g = ((id) & 0x0000FF00) >> 8;
	int b = ((id) & 0x00FF0000) >> 16;

	std::cout << "r, " << r << " g, " << g << " b, " << b << std::endl;

}

void RubiksCube::printRGB()
{
	printf(" Wall Right: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "id :" << walls[myRight]->getWall()[i][j]->getID();
			calcRGB(walls[myRight]->getWall()[i][j]->getID());
		}
		printf("\n");
	}
	printf(" Wall UP: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "id :" << walls[U]->getWall()[i][j]->getID();
			calcRGB(walls[U]->getWall()[i][j]->getID());
		}
			
		printf("\n");
	}
	printf(" Wall DOWN: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "id :" << walls[D]->getWall()[i][j]->getID();
			calcRGB(walls[D]->getWall()[i][j]->getID());
		}
			
		printf("\n");
	}
	printf(" Wall LEFT: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "id :" << walls[myLeft]->getWall()[i][j]->getID();
			calcRGB(walls[myLeft]->getWall()[i][j]->getID());
		}
			
		printf("\n");
	}
	printf(" Wall BACK: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "id :" << walls[B]->getWall()[i][j]->getID();
			calcRGB(walls[B]->getWall()[i][j]->getID());
		}
			
		printf("\n");
	}
	printf(" Wall FORWARD: \n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "id :" << walls[F]->getWall()[i][j]->getID();
			calcRGB(walls[F]->getWall()[i][j]->getID());
		}
			
		printf("\n");
	}
}
void RubiksCube::WhenPicked()
{
	pickedShape = -1;
}
RubiksCube::~RubiksCube(void)
{

}
