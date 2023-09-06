#ifndef SHADER_HHP
#define SHADER_HHP

#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader
{
public:
    // remove the basic constructor
    Shader() = delete;
    // remove also the copy constructor
    Shader(const Shader & ) = delete ;
    ~Shader();
    // the program ID
    GLuint id ;

    // the constructor that reads and build the shader
    Shader(const std::string& vertexPath, const std::string& fragementPath) ;
    // (use/activate) the shader 
    void use();
    //utility uniform functions
    void setBool(const  std::string& name, bool  value) const ;
    void setInt(const   std::string& name, int   value) const ;
    void setFloat(const std::string& name, float value) const;
    


private:
    GLuint vertex, fragment ;
    


    void vShaderCompilation(const char* vShaderCode) ;
    void fShaderCompilation(const char* fShaderCode) ;
    void shaderProgramLinker() ;
    

};

#endif