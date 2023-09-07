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
                                    1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                                    1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                                   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                                   -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
    unsigned char *e;
    p_kernelLauncher = new KernelLauncher(p_width, p_height) ;
  
    drawing(p_window, programShader);
 
   
}


void createFlashlightTexture(uchar *flashlightTexture) {
    int textureSize = 512;  // Adjust the size as needed
    float centerX = textureSize / 2.0f;
    float centerY = textureSize / 2.0f;
    float radius = textureSize / 4.0f;  // Adjust the radius as needed

    for (int y = 0; y < textureSize; y++) {
        for (int x = 0; x < textureSize; x++) {
            float distance = sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
            int index = (y * textureSize + x) * 4; // Calculate the index for RGBA components

            if (distance < radius) {
                // Inside the circle, set RGB to white (fully lit) and A to 255 (fully opaque)
                flashlightTexture[index] =     255;     // Red (R)
                flashlightTexture[index + 1] = 255; // Green (G)
                flashlightTexture[index + 2] = 255; // Blue (B)
                flashlightTexture[index + 3] = 255; // Alpha (A)
            } else {
                // Outside the circle, set RGB to black (no light) and A to 0 (fully transparent)
                flashlightTexture[index] = 0;     // Red (R)
                flashlightTexture[index + 1] = 0; // Green (G)
                flashlightTexture[index + 2] = 0; // Blue (B)
                flashlightTexture[index + 3] = 0; // Alpha (A)
            }
        }
    }
}

void WindowManager::drawing(GLFWwindow * window, Shader& program){
    uchar*data_host  = new uchar[4*p_height*p_width*sizeof(uchar)];
    createFlashlightTexture(data_host);

    GLuint mouseLocation      = glGetUniformLocation(program.id, "mouse");
    while (!glfwWindowShouldClose(window))
    {   
       p_kernelLauncher->Launcher(data_host, p_kernelLauncher->mouse.x,p_kernelLauncher->mouse.y);
       if (data_host){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_host);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data_host);
        glGenerateMipmap(GL_TEXTURE_2D);
        }
       else{
        std::cout << "Failed to load texture" << std::endl;
        }
       
       glClearColor(0.0f, 0.0f, 0.0f, 1.0f) ;
       glClear(GL_COLOR_BUFFER_BIT) ;

       glfwGetCursorPos(window, &p_kernelLauncher->mouse.x, &p_kernelLauncher->mouse.y ) ;
       
       p_kernelLauncher->mouse.x = (p_kernelLauncher->mouse.x/p_width)*2.0f- 1 ;
       p_kernelLauncher->mouse.x =  p_kernelLauncher->mouse.x > 1.0f ? 1.0f :p_kernelLauncher->mouse.x < -1.0f ? -1.0f:p_kernelLauncher->mouse.x ;

       p_kernelLauncher->mouse.y = ((p_height- p_kernelLauncher->mouse.y)/p_height)*2- 1 ;
       p_kernelLauncher->mouse.y = p_kernelLauncher->mouse.y > 1.0f ? 1.0f : p_kernelLauncher->mouse.y < -1.0f ? -1.0f:p_kernelLauncher->mouse.y ;

   
       if (p_kernelLauncher->mouse.x ==1 or p_kernelLauncher->mouse.x == 0 or p_kernelLauncher->mouse.y ==1 or p_kernelLauncher->mouse.y == 1) ;
       else glUniform2f(mouseLocation,  p_kernelLauncher->mouse.x, p_kernelLauncher->mouse.y) ; 
       
       glBindTexture(GL_TEXTURE_2D, _texture);
       program.use() ;
       
       glBindVertexArray(_vao);
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       
       
       glBindVertexArray(0);
       glfwSwapBuffers(window);
       glfwPollEvents() ;

      
    }

     if (data_host) {
        delete[] data_host;
        data_host = nullptr;
    }
     
     glfwTerminate() ;
}
void WindowManager::simulation(){
    renderer();
}
