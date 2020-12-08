#include "InputManager.h"
#include "rubikscube.h"
#include "glm/glm.hpp"

int main(int argc,char *argv[])
{
	const int DISPLAY_WIDTH = 1600;
	const int DISPLAY_HEIGHT = 800;
	const float CAMERA_ANGLE = 60.0f;
	const float NEAR = 1.0f;
	const float FAR = 1000.0f;
	const int infoIndx = 2; 
	std::list<int> x, y;
	int n_Bonus = 3; // <<< Cube Size
	x.push_back(DISPLAY_WIDTH );
	y.push_back(DISPLAY_HEIGHT);
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Renderer* rndr = new Renderer(CAMERA_ANGLE, (float)DISPLAY_WIDTH  / DISPLAY_HEIGHT, NEAR, FAR); // adding a camera
	RubiksCube *scn = new RubiksCube(n_Bonus);  //initializing scene
	
	Init(display); //adding callback functions
	scn->Init();    //adding shaders, textures, shapes to scene
	rndr->Init(scn,x,y); // adding scene and viewports to the renderer
	display.SetRenderer(rndr);  // updating renderer in as a user pointer in glfw
	//For 2D rendering
	rndr->Create2Dmaterial(1);
	//Orthographic camera.
	rndr->AddCamera(glm::vec3(0,0,0),0,1,-1,1,infoIndx);
	rndr->MoveCamera(0, scn->zTranslate, +0.8f* n_Bonus);
	rndr->BindViewport2D(infoIndx);

	while(!display.CloseWindow())
	{
		rndr->DrawAll();
		scn->Motion();
		display.SwapBuffers();
		display.PollEvents();		
	}
	delete scn;
	return 0;
}
