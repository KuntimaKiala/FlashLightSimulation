#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>
#include "shader.hpp"
#include "KernelLauncher.cuh"
#include "cmath"
namespace VertexAttributes{
	enum VertexAttributes{
		vao_position=0,
		vao_color=1,
		vao_texture=2,

	};
};
class WindowManager
{
public:
	WindowManager()=delete;
	WindowManager(int width=500, int height=500,  const char* windowName="FlashLight Simulation");
	~WindowManager() ;
	void GLFWindowGeneration() ;
	void simulation() ; // game loop 
	
private:
	void initialize() ; // a function that initializes glfw
	void renderer()  ; // a function that renders the window, contains the loop 
	void drawing(GLFWwindow *  window, Shader& program)  ; // a function that actually draws stuffs on screen
	void createFlashlightTexture(uchar *flashlightTexture);
	GLFWwindow *  p_window ;
	int p_width, p_height ;
	const char*  p_windowName{nullptr};
	GLuint _vbo, _ebo, _vao ;
	GLuint _image ;
	GLuint _texture;
	KernelLauncher* p_kernelLauncher ; 
	float p_radius{0.25f};
	
};

