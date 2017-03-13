//
//  YcoreIM4ObjCService.h
//  IM4ObjC
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ImageMagickEngine.h"

@interface YcoreIM4ObjCService : NSObject

-(void)transformatWithSourcePath:(NSString *)sourcePath destPath:(NSString *)destPath;

-(void)thumnailImageWithSourcePath:(NSString *)sourcePath
                          destPath:(NSString *)destPath
                       targetWidth:(int)width
                      targerHeight:(int)height;
-(void)acquireImageInfoWithSourcePath:(NSString *)sourcePath
                             destPath:(NSString *)destPath;
-(void)cropImageCutWithSourcePath:(NSString *)sourcePath
                         destPath:(NSString *)destPath
                           pointX:(int)pointX
                           pointY:(int)pointY
                            width:(int)width
                           height:(int)height;
-(void)resizeImageWithMode:(ImageOptModeType)modeType
                sourcePath:(NSString *)sourcePath
                  destPath:(NSString *)destPath
                     width:(int)width
                    height:(int)height
                   quality:(double)quality;


@end
