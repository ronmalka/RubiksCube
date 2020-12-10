#pragma once   //maybe should be static class
#include "display.h"
#include "renderer.h"
#include "rubikscube.h"
#include <Engine3D\renderer.h>
#include <iostream>
#include <random>
#include <windows.h>
#define myRight 0
#define myLeft 1
#define U 2
#define D 3
#define B 4
#define F 5
#define CW 1
#define CCW -1

Display* myDisp;
void doRotate(RubiksCube* scn,Renderer* rndr,int wall) {
	for (float i = 0; i < 90.f; ++i) {
		scn->doRotate(wall);
		rndr->DrawAll();
		scn->Motion();
		myDisp->SwapBuffers();
		Sleep(scn->getGlobalSpeed());
	}
	scn->getWall(wall)->rotate();
}
	void mouse_callback(GLFWwindow* window,int button, int action, int mods)
	{	
		if(action == GLFW_PRESS )
		{
			Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
			RubiksCube* scn = (RubiksCube*)rndr->GetScene();
			double x2,y2;
			glfwGetCursorPos(window,&x2,&y2);
			if (rndr->Picking((int)x2, (int)y2))
			{
				std::cout << "picked : " << std::endl;
				rndr->UpdatePosition(x2, y2);
			}

			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
			{
				std::cout << "right_button : " << std::endl;
				
			}
				
		}
	}
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubiksCube* scn = (RubiksCube*)rndr->GetScene();
		if (yoffset > 0) {
			rndr->MoveCamera(0, scn->zTranslate, 0.4f);
		}
		else {
			rndr->MoveCamera(0, scn->zTranslate, -0.4f);
		}		
	}
	
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubiksCube* scn = (RubiksCube*)rndr->GetScene();

		rndr->UpdatePosition((float)xpos,(float)ypos);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			rndr->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
		}

	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		
		rndr->Resize(width,height);
		
	}
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubiksCube* scn = (RubiksCube*)rndr->GetScene();

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;

			case GLFW_KEY_UP:
				//rndr->MoveCamera(0, scn->zTranslate, 0.4f);
				break;
			case GLFW_KEY_DOWN:
				//rndr->MoveCamera(0, scn->zTranslate, -0.4f);
				break;

			case GLFW_KEY_SPACE:
				std::cout << "direction" << std::endl;
				scn->setGlobalDir();
				break;

			case GLFW_KEY_U:
			{
				std::cout << "up" << std::endl;
				doRotate(scn,rndr, U);
				break;
			}
			case GLFW_KEY_D:
			{
				std::cout << "down" << std::endl;
				doRotate(scn, rndr, D);
				break;
			}
			case GLFW_KEY_R:
			{
				std::cout << "right" << std::endl;
				doRotate(scn, rndr, myRight);
				break;
			}
			case GLFW_KEY_L:
			{
				std::cout << "left" << std::endl;
				doRotate(scn, rndr, myLeft);
				break;
			}
			case GLFW_KEY_F:
			{
				std::cout << "front" << std::endl;
				doRotate(scn, rndr, F);
				break;
			}
			case GLFW_KEY_B:
			{
				std::cout << "back" << std::endl;
				doRotate(scn, rndr, B);
				break;
			}
			case GLFW_KEY_M:
			{
				std::cout << "mix" << std::endl;
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(0, 5);
				for (int k = 0; k < 10; ++k) {
					int dice_roll = distribution(generator);
					doRotate(scn, rndr, dice_roll);
				}
				break;
			}
			case GLFW_KEY_Z:
			{
				scn->decGlobalSpeed();
				std::cout << "globalSpeed : " << scn->getGlobalSpeed() << std::endl;
				break;
			}
			case GLFW_KEY_A:
			{
				scn->incGlobalSpeed();
				std::cout << "globalSpeed : " << scn->getGlobalSpeed() << std::endl;
				break;
			}
			default:
				break;
			}
		}
	}

	void Init(Display &display)
	{
		
		display.AddKeyCallBack(key_callback);
		display.AddMouseCallBacks(mouse_callback,scroll_callback,cursor_position_callback);
		display.AddResizeCallBack(window_size_callback);
		myDisp = &display;

	}
