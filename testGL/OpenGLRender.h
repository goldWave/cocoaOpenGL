//
//  OpenGLRender.hpp
//  testGL
//
//  Created by jimbo on 2017/6/19.
//  Copyright © 2017年 naver. All rights reserved.
//


#pragma once
#include <iostream>

class OpenGLRender
{
public:
    OpenGLRender();
    void Initialize(float width, float height,std::string shaderPath);
    void GiveRender();
    void ChangeImage(std::string imagePath);
private:
    
};


