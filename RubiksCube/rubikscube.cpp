#include "rubikscube.h"
#include <iostream>
#include "GL/glew.h"


void RubiksCube::printMat()
{
	printf(" Wall Right: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << " " << walls[R]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall UP: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << " " << walls[U]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall DOWN: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << " " << walls[D]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall LEFT: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << " " << walls[L]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall BELOW: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << " " << walls[B]->getWall()[i][j]->getID();
		printf("\n");
	}
	printf(" Wall FORWARD: \n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
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

RubiksCube::RubiksCube() : Scene()
{
	walls = new Wall * [6];
	walls[R] = new Wall(glm::vec3(1.f,0.f ,0.f),CW,&globalDir);
	walls[L] = new Wall(glm::vec3(-1.f, 0.f, 0.f), CW, &globalDir);
	walls[U] = new Wall(glm::vec3(0.f, 1.f, 0.f), CW, &globalDir);
	walls[D] = new Wall(glm::vec3(0.f, -1.f, 0.f), CW, &globalDir);
	walls[F] = new Wall(glm::vec3(0.f, 0.f, 1.f), CW, &globalDir);
	walls[B] = new Wall(glm::vec3(0.f, 0.f, -1.f),CW, &globalDir);
	globalDir = 1;
	globalSpeed = 5;

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

	int pickCounter = 0;
	int loc [3] = { -2,0,2 };
	//rubCube = new MyCube* **[3];
	for (int x = 0; x < 3; x++)
	{
		//rubCube[z] = new MyCube* *[3];
		for (int y = 0; y < 3; y++)
		{
			//rubCube[y][z] = new MyCube* [3];
			for (int z = 0; z < 3; z++)
			{
				AddShape(Cube, -1, TRIANGLES);
				SetShapeShader(pickCounter, 1);
				SetShapeMaterial(0, 0);
				pickedShape = pickCounter;
				ShapeTransformation(xTranslate, -2 + 2*x);
				ShapeTransformation(yTranslate, - 2 + 2*y);
				ShapeTransformation(zTranslate, -2 +2*z);
				MyCube* c = new MyCube(-2 + 2 * x, -2 + 2 * y, -2 + 2 * z,pickCounter);
				std::cout << pickCounter << "  "<<"loc  ( x  "<< x << " ," << " y "<< y << " ," << " z  "<< z << ")" <<std::endl;
				if (x == 0) {
					walls[L]->setCubeAt(y,z,c);
				}
				else if (x == 2) {
					walls[R]->setCubeAt(y,2-z,c);
				}
				if (y==0) {
					walls[D]->setCubeAt(2-x,z,c);
				}
				else if (y == 2) {
					walls[U]->setCubeAt(x,z,c);
				}
				if (z == 0) {
					walls[B]->setCubeAt(x,y,c);
				}
				else if (z == 2) {
					walls[F]->setCubeAt(x,2-y,c);
				}
				pickCounter++;
				pickedShape = -1;
			}
		}

	}
	printMat();
	
	
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
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			MyCube* c = myCubes[i][j];
			pickedShape = c->getID();
			shapes[pickedShape]->RotateTranslate(myWall->getDir()*globalDir * 1.f, myWall->getAxis(), 0);
			pickedShape = -1;
		}
	}
	//walls[wall]->rotate();
}

RubiksCube::~RubiksCube(void)
{

}
