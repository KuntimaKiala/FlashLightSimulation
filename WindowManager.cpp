#include "WindowManager.hpp"

WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}


void WindowManager::initialize(int width, int height,  const char* windowName ) {



    glfwInit() ;
    glfwInitHint(GLFW_VERSION_MINOR, 3);
    glfwInitHint(GLFW_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // window creation 
    GLFWwindow *window =glfwCreateWindow( width, height, windowName, NULL, NULL );


    if (window == NULL){

        std::cout <<"WINDOWMANAGER::BUILD::FAILED\n";
        std::cout <<"WINDOWMANAGER::RETURN::VOID\n" ;
        return ;

    }
    glfwMakeContextCurrent(window) ;


}