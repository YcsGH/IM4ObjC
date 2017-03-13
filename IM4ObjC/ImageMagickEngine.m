//
//  ImageMagickEngine.m
//  IM4ObjC
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import "ImageMagickEngine.h"
#import "YcoreIM4ObjCService.h"

@interface ImageMagickEngine ()
@property (nonatomic,strong) YcoreIM4ObjCService *magickService;
@end

@implementation ImageMagickEngine

-(void)im_transformatWithSourcePath:(NSString *)sourcePath
                           destPath:(NSString *)destPath {
    [self.magickService transformatWithSourcePath:sourcePath destPath:destPath];
}

-(void)im_thumnailImageWithSourcePath:(NSString *)sourcePath
                             destPath:(NSString *)destPath
                          targetWidth:(int)width
                         targerHeight:(int)height{
    [self.magickService thumnailImageWithSourcePath:sourcePath destPath:destPath targetWidth:width targerHeight:height];
}

-(void)im_acquireImageInfoWithSourcePath:(NSString *)sourcePath
                             destPath:(NSString *)destPath {
    [self.magickService acquireImageInfoWithSourcePath:sourcePath destPath:destPath];
}

-(void)im_cropImageCutWithSourcePath:(NSString *)sourcePath
                         destPath:(NSString *)destPath
                           pointX:(int)pointX
                           pointY:(int)pointY
                            width:(int)width
                           height:(int)height {
    [self.magickService cropImageCutWithSourcePath:sourcePath destPath:destPath pointX:pointX pointY:pointY width:width height:height];
}

-(void)im_resizeImageWithMode:(ImageOptModeType)modeType
                   sourcePath:(NSString *)sourcePath
                     destPath:(NSString *)destPath
                        width:(int)width
                       height:(int)height
                      quality:(double)quality {
    [self.magickService resizeImageWithMode:modeType sourcePath:sourcePath destPath:destPath width:width height:height quality:quality];
}


#pragma mark ====== lazy ======

-(YcoreIM4ObjCService *)magickService {
    if (!_magickService) {
        _magickService = [[YcoreIM4ObjCService alloc]init];
    }
    return _magickService;
}

@end
