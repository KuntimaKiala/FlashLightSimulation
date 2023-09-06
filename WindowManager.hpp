#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>


class WindowManager
{
public:
	WindowManager();
	WindowManager(int width=500, int height=500,  const char* windowName="FlashLight Simulation");
	~WindowManager() ;
	
	void run() ; // game loop 
	void GLFWindowGeneration() ;
private:
	void initialize() ; // a function that initializes glfw
	void renderer()  ; // a function that renders the window
	GLFWwindow *  p_window ;
	int p_width, p_height ;
	const char*  p_windowName{nullptr};
};

