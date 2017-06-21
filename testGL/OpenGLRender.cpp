//
//  OpenGLRender.cpp
//  testGL
//
//  Created by jimbo on 2017/6/19.
//  Copyright © 2017年 naver. All rights reserved.
//

#include <iostream>
#include "glew.h"
#include "Shader.h"
#include "OpenGLRender.h"
#include <OpenGL/OpenGL.h>
#include "stb_image.h"

Shader rectanShader;
Shader borderShader;
GLuint texture;
GLuint VBO, VAO;

OpenGLRender::OpenGLRender()
{
    
}

void OpenGLRender::Initialize(float width, float height, std::string shaderPath) {

    // do some GL setup
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClearDepth(1.0f);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    
    glViewport(0, 0, width, height);
    
#ifdef __APPLE__
    glewExperimental = GL_TRUE;//TODO
#endif
    glewInit();
    
    rectanShader.setupShader((shaderPath + "/shader.vs").c_str(), (shaderPath + "/shader.fs").c_str());
    borderShader.setupShader((shaderPath + "/border.vs").c_str(), (shaderPath + "/border.fs").c_str());
    float vertices[] = {
        // positions             // texture coords
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  // top left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f // bottom right
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float) , (void *)0);
    glEnableVertexAttribArray(0);

    //tex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //load and create texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    ChangeImage((shaderPath + "/women.jpg"));
}


void OpenGLRender::GiveRender() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    rectanShader.Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
}
void OpenGLRender::ChangeImage(std::string imagePath) {
    
    int texWidth, texHeight, nrChannels;
    unsigned char *data = stbi_load(imagePath.c_str(), &texWidth, &texHeight, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);
}
