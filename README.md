# cocoaOpenGL
a simple openGL demo for mac OS, 


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
    
