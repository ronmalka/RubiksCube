#pragma once   //maybe should be static class
#include "display.h"
#include "renderer.h"
#include "rubikscube.h"
#include <Engine3D\renderer.h>
#include <iostream>
#define R 0
#define L 1
#define U 2
#define D 3
#define B 4
#define F 5
#define CW 1
#define CCW -1
Display* myDisp;
	void mouse_callback(GLFWwindow* window,int button, int action, int mods)
	{	
		if(action == GLFW_PRESS )
		{
			Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
			RubiksCube* scn = (RubiksCube*)rndr->GetScene();
			double x2,y2;
			glfwGetCursorPos(window,&x2,&y2);
			if (rndr->Picking((int)x2, (int)y2))
				rndr->UpdatePosition(x2,y2);
		}
	}
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Renderer* rndr = (Renderer*)glfwGetWindowUserPointer(window);
		RubiksCube* scn = (RubiksCube*)rndr->GetScene();
		std::cout << xoffset << " " << yoffset << std::endl;
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
				scn->setGlobalDir();
				break;

			case GLFW_KEY_U:
			{
				for (float i = 0; i < 90.f;++i) {
					scn->doRotate(U);
					rndr->DrawAll();
					scn->Motion();
					myDisp->SwapBuffers();
				}
				scn->getWall(U)->rotate();
				break;
			}
			case GLFW_KEY_D:
			{
				for (float i = 0; i < 90.f; ++i) {
					scn->doRotate(D);
					rndr->DrawAll();
					scn->Motion();
					myDisp->SwapBuffers();
				}
				scn->getWall(D)->rotate();
				break;
			}
			case GLFW_KEY_R:
			{
				for (float i = 0; i < 90.f; ++i) {
					scn->doRotate(R);
					rndr->DrawAll();
					scn->Motion();
					myDisp->SwapBuffers();
				}
				scn->getWall(R)->rotate();
				break;
			}
			case GLFW_KEY_L:
			{
				for (float i = 0; i < 90.f; ++i) {
					scn->doRotate(L);
					rndr->DrawAll();
					scn->Motion();
					myDisp->SwapBuffers();
				}
				scn->getWall(L)->rotate();
				break;
			}
			case GLFW_KEY_F:
			{
				for (float i = 0; i < 90.f; ++i) {
					scn->doRotate(F);
					rndr->DrawAll();
					scn->Motion();
					myDisp->SwapBuffers();
				}
				scn->getWall(F)->rotate();
				break;
			}
			case GLFW_KEY_B:
			{
				for (float i = 0; i < 90.f; ++i) {
					scn->doRotate(B);
					rndr->DrawAll();
					scn->Motion();
					myDisp->SwapBuffers();
				}
				scn->getWall(B)->rotate();
				break;
			}
			case GLFW_KEY_Z:
			{
				scn->decGlobalSpeed();
				break;
			}
			case GLFW_KEY_A:
			{
				scn->incGlobalSpeed();
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
