#include "shader.hpp"

void Shader::use(){

    glUseProgram(id) ;

}

Shader::~Shader(){}


Shader::Shader(const std::string& vertexPath, const std::string& fragementPath) {
    //1- retrieving the vertex and fragment source from a text file, given by the file paths
    std::string   vertexCode; // where 
    std::string   fragmentCode ;
    std::ifstream vShaderFile ;
    std::ifstream fShaderFile ;

    // ensuring that ifstream object throws an exception 
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit) ; // exception handler for the vertex shader file
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit) ; // exception handler for the fragement shader file

    try {

        // open a files (vertex/fragment) file
        vShaderFile.open(vertexPath) ; // opening the vertex file
        fShaderFile.open(fragementPath) ; // opening the fragement file
        
        std::stringstream vShaderStream, fShaderStream ;
        //xxxx.rdbuf() returns a pointer to the stream buffer, 
        //and the << operator reads from that buffer and loads the data into the std::stringstream object.
        vShaderStream << vShaderFile.rdbuf() ; 
        fShaderStream << fShaderFile.rdbuf() ;

        // closing the handler
        vShaderFile.close();
        fShaderFile.close() ;

        // conert stream into string 
        vertexCode   = vShaderStream.str() ;
        fragmentCode = fShaderStream.str() ;
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        exit(0) ;
    }

    const char*  vShaderCode = vertexCode.c_str() ;
    const char*  fShaderCode = fragmentCode.c_str() ;

    // ccreating, sourcing and compiling the shaders (vertex/fragment)
    vShaderCompilation(vShaderCode);
    fShaderCompilation(fShaderCode);
    // Linking the shaders to the graphic pipeline
    shaderProgramLinker() ;
    


}

void Shader::shaderProgramLinker() {
    //create the id
    id  = glCreateProgram();
    // attach program with each of the shader stage (vertex/fragement)
    glAttachShader(id,vertex) ;
    glAttachShader(id,fragment) ;
    glLinkProgram(id) ;

    int sucess ;
    char InfoLog[512];
    glGetProgramiv(id,GL_LINK_STATUS, &sucess);
    if(!sucess){
        glGetProgramInfoLog(id, 512, NULL, InfoLog);
        std::cout << "ERROR::PROGRAM::SHADER::FAILED\nERROR MESSAGE : " << InfoLog << std::endl ;
        return ;
    }

    glDeleteShader(vertex) ;
    glDeleteShader(fragment) ;
}

void Shader::vShaderCompilation(const char* vShaderCode){
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    int sucess ;
    char InfoLog[512] ;

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);
    if(!sucess){
        glGetShaderInfoLog(vertex, 512, NULL, InfoLog) ;
        std::cout << "ERROR::VERTEX::SHADER::PROGRAM::FAILED\nERROR MESSAGE : " << InfoLog << std::endl ;
        return ;

    }
}

void Shader::fShaderCompilation(const char* fShaderCode){
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    int sucess ;
    char InfoLog[512] ;

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);
    if(!sucess){
        glGetShaderInfoLog(fragment, 512, NULL, InfoLog) ;
        std::cout << "ERROR::FRAGMENT::SHADER::PROGRAM::FAILED\nERROR MESSAGE : " << InfoLog << std::endl ;
        return ;      
    }
}


