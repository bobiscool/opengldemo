//
//  main.cpp
//  opengl3
//
//  Created by mac on 18/1/27.
//  Copyright © 2018年 mac. All rights reserved.
//
#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode);


const GLuint WIDTH = 800,HEIGHT = 600;


// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x,position.y,position.z,1.0);\n"
"}\0"
;


const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n\0"
;
// 着色器 书写 出了点问题

int main(){
    // init glfw
    glfwInit();
    
    // 设置窗口 属性
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    
    // 创建一个 窗口 对象
    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"learnOpenGL",nullptr,nullptr);
    //
    glfwMakeContextCurrent(window);
    // 设置回调
    glfwSetKeyCallback(window,key_callback);
    
    // 下面是干啥的 还不知道
    glewExperimental = GL_TRUE;
    
    glewInit();
    
    
    // 设置 视窗 尺寸
    int width,height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0,0,width,height);
    
    
    //顶点着色器
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    
    //
    GLint success; // 检测是否编译成功
    GLchar infoLog[512];//
    
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);//& 在函数传值里面 是什么意思  是不是 创建一个值 然后 在函数里面 去取值
    
    if(!success){
        glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
        std::cout << "ERROR::SHZDER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    // Fragement shader 片元着色器
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    
    // 检测编译错误
    
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
        std::cout <<"ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    
    // 链接 着色器
    GLuint shaderProgram = glCreateProgram(); // 创建着色器 程序
    glAttachShader(shaderProgram,vertexShader); // 将着色器 附着在 着色程序
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    
    // 是否 link 错误
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout <<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
    }
    
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    
    // 设置完 着色器  开始设置 绘制程序
    GLfloat vertices[]={
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.5f, 0.5f,0.0f
    };
    
    GLuint VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    // 绑定一堆东西
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindVertexArray(0);
    
    
    while(!glfwWindowShouldClose(window)){
        // 研究事件
        glfwPollEvents();
        
        // 清除 颜色
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 绘制 第一个三角形
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);
        //
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    
    //
    glfwTerminate();
    
    return 0;
}


void key_callback(GLFWwindow* window,int key,int scancode,int action,int mode){
    if (key == GLFW_KEY_ESCAPE&&action ==GLFW_PRESS) {
        glfwSetWindowShouldClose(window,GL_TRUE);
    }
}



