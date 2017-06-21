//
//  ViewController.m
//  testGL
//
//  Created by jimbo on 2017/6/19.
//  Copyright © 2017年 naver. All rights reserved.
//

#include <OpenGL/OpenGL.h>
#import  "ViewController.h"
#include "OpenGLRender.h"
#import  "GLView.h"
#import  "GLHander.h"

@interface ViewController ()
{
    NSTimer *_timer;
    OpenGLRender _openRender;
}
@property (weak) IBOutlet GLView *openGLView;
@property GLHander *glHander;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //
    self.glHander = [[GLHander alloc] init];
    [self.glHander setupGLConfigWithView:self.openGLView];
    _openRender = OpenGLRender();
    NSString *sourcePath = [NSBundle mainBundle].resourcePath;
    _openRender.Initialize(self.openGLView.frame.size.width, self.openGLView.frame.size.height, std::string([sourcePath UTF8String]));
    
    _timer = [NSTimer timerWithTimeInterval:(1.0f / 30.0f)
                                     target:self
                                   selector:@selector(timerFireMethod:)
                                   userInfo:nil
                                    repeats:YES];
    [[NSRunLoop currentRunLoop] addTimer:_timer forMode:NSDefaultRunLoopMode];
    
 
    NSLog(@"ee");
}

- (void)timerFireMethod:(NSTimer *)theTimer
{
    _openRender.GiveRender();
    [self.openGLView.openGLContext flushBuffer];
}

- (IBAction)choseImageClick:(id)sender {
    NSOpenPanel* openPanel = [NSOpenPanel openPanel];
    
    openPanel.showsResizeIndicator = YES;
    openPanel.showsHiddenFiles = NO;
    openPanel.canChooseDirectories = NO;
    openPanel.canCreateDirectories = NO;
    openPanel.allowsMultipleSelection = NO;
    openPanel.allowedFileTypes = @[@"png", @"jpg", @"jpeg", @"tiff", @"svg"];
    
    [openPanel beginSheetModalForWindow:self.view.window
                      completionHandler:^(NSInteger result) {
                          if (result==NSModalResponseOK) {
                              NSURL *selection = openPanel.URLs[0];
                              NSString* path = [selection.path stringByResolvingSymlinksInPath];
                              _openRender.ChangeImage(std::string([path UTF8String]));
                          }
                          
                      }];
}


@end
