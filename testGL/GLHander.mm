//
//  GLHander.m
//  testGL
//
//  Created by jimbo on 2017/6/19.
//  Copyright © 2017年 naver. All rights reserved.
//
#include "GLHander.h"

@implementation GLHander

- (void)setupGLConfigWithView:(GLView *)glView {
    
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, 32,
        0
    };
    
    NSOpenGLPixelFormat *format = [[NSOpenGLPixelFormat alloc]
                                   initWithAttributes:attr];
    NSOpenGLContext *context = [[NSOpenGLContext alloc] initWithFormat:format
                                                          shareContext:nil];
    
    [glView setOpenGLContext:context];
    [glView.openGLContext makeCurrentContext];
}

@end
