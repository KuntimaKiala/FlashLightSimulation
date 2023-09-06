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
        glfwTerminate();
        return ;

    }
    glfwMakeContextCurrent(p_window) ;

    // load the OpenGL Function through GLAD, wthout this, function like glClear does not work
    int error = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress );
    if (!error){
        std::cout <<"WINDOWMANAGER::BUILD::GLAD::FAILED\n";
        std::cout <<"WINDOWMANAGER::RETURN::VOID\n" ;
        glfwTerminate();
        return ;
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
    
    // Creating an ID    
    glGenVertexArrays(1,&_vao) ;
    glGenBuffers(1, &_vbo) ;
    glGenBuffers(1, &_ebo) ;

    // binding VAO
    glBindVertexArray(_vao);

    //bind and send data VBO 
    glBindBuffer(GL_ARRAY_BUFFER, _vbo) ;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    //bind and send data EBO 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );
    
     //position attribute
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(VertexAttributes::vao_position);
    //color attribute
    glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)) );
    glEnableVertexAttribArray(VertexAttributes::vao_color);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(VertexAttributes::vao_texture);
    
    
    
    // load and create a texture 
    // -------------------------
    
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("./resources/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    drawing(p_window, programShader);
 
   
}


void WindowManager::drawing(GLFWwindow * window, Shader& program){

    while (!glfwWindowShouldClose(window))
    {   
        
       
       glClearColor(0.5f, 0.3f, 0.3f, 1.0f) ;
       glClear(GL_COLOR_BUFFER_BIT) ;
    
       glBindTexture(GL_TEXTURE_2D, _texture);
       program.use() ;
       glBindVertexArray(_vao);
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

       
       glBindVertexArray(0);
       glfwSwapBuffers(window);
       glfwPollEvents() ;

      
    }

     glfwTerminate() ;
}
void WindowManager::simulation(){
    renderer();
}
