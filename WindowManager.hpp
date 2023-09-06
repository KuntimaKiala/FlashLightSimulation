#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>


class WindowManager
{
public:
	WindowManager();
	~WindowManager() ;
	void initialize(int width, int height,  const char* windowName) ; // a function that initializes glfw
	
private:

};

