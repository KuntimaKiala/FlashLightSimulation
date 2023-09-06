#include "WindowManager.hpp"

WindowManager::WindowManager(int width, int height,  const char* windowName) : 
p_width(width), p_height(height), p_windowName(windowName)
{
    //Initialiaze OpenGL
    initialize();
}


WindowManager::~WindowManager()
{   
    
 
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

        std::cout <<"WINDOWMANAGER::BUILD::WINDOW::FAILED\n";
        std::cout <<"WINDOWMANAGER::RETURN::VOID\n" ;
        return ;

    }
    glfwMakeContextCurrent(p_window) ;

    // load the OpenGL Function through GLAD, wthout this, function like glClear does not work
    int error = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress );
    if (!error){
        std::cout <<"WINDOWMANAGER::BUILD::GLAD::FAILED\n";
        std::cout <<"WINDOWMANAGER::RETURN::VOID\n" ;
    }


}



void WindowManager:: renderer(){
    
    [[maybe_unused]]float vertices[] = {
                                    // positions          // colors           // texture coords
                                    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                                    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                                   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                                   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    [[maybe_unused]]unsigned int indices[] = {  
                                    0, 1, 3, // first triangle
                                    1, 2, 3  // second triangle
    };

    // compile the shader prgram 
    Shader programShader("./texture.vs", "./texture.fs") ;
    
    glGenVertexArrays(1,&_vao) ;
    glGenBuffers(1, &_vbo) ;
    glGenBuffers(1, &_ebo) ;


    drawing(p_window);
 
   
}


void WindowManager::drawing(GLFWwindow * window){

    while (!glfwWindowShouldClose(window))
    {   
        
       glClearColor(0.5f, 0.3f, 0.3f, 1.0f) ;
       glClear(GL_COLOR_BUFFER_BIT) ;
       glfwSwapBuffers(window);
       glfwPollEvents() ;

    }

     glfwTerminate() ;
}
void WindowManager::simulation(){
    renderer();
}
