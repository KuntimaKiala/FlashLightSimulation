#include "WindowManager.hpp"

WindowManager::WindowManager(int width, int height,  const char* windowName) : 
p_width(width), p_height(height), p_windowName(windowName)
{
    //Initialiaze OpenGL
    initialize();
}


WindowManager::~WindowManager()
{   
    
    glfwTerminate() ; // terminate the window
}

void WindowManager::initialize() {
    glfwInit() ;
    glfwInitHint(GLFW_VERSION_MINOR, 3);
    glfwInitHint(GLFW_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}
void WindowManager::GLFWindowGeneration() {


    
    // window creation 
    p_window = glfwCreateWindow( p_width, p_height, p_windowName, NULL, NULL );


    if (p_window == NULL){

        std::cout <<"WINDOWMANAGER::BUILD::FAILED\n";
        std::cout <<"WINDOWMANAGER::RETURN::VOID\n" ;
        return ;

    }
    glfwMakeContextCurrent(p_window) ;


}



void WindowManager:: renderer(){

    while (!glfwWindowShouldClose(p_window))
    {
        glfwSwapBuffers(p_window);
        glfwPollEvents() ;
    }
    
}

void WindowManager::run(){
    renderer();
}
