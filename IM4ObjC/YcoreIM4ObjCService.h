//
//  YcoreIM4ObjCService.h
//  Temproject
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YcoreIM4ObjCService : NSObject

-(void)transformatWithSourcePath:(NSString *)sourcePath destPath:(NSString *)destPath;

-(void)thumnailImageWithSourcePath:(NSString *)sourcePath
                          destPath:(NSString *)destPath
                       targetWidth:(float)width
                      targerHeight:(float)height;
-(void)acquireImageInfoWithSourcePath:(NSString *)sourcePath
                             destPath:(NSString *)destPath;




@end
