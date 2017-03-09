//
//  ImageMagickEngine.h
//  Temproject
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ImageMagickEngine : NSObject

#pragma mark ====== 图片格式转换 ======

/**
 * 图片格式转换
 * @param sourcePath 原图片路径 eg:/Caches/aa.jpg
 * @param destPath 目标图片路径 eg:/Caches/aa.png
 *
 */
-(void)im_transformatWithSourcePath:(NSString *)sourcePath destPath:(NSString *)destPath;

/**
 * 获取指定宽高的缩略图
 * @param sourcePath 原图片路径 eg:/Caches/aa.jpg
 * @param destPath 目标图片路径 eg:/Caches/aa.jpg
 * @param width 目标图片长度
 * @param height 目标图片高度
 */
-(void)im_thumnailImageWithSourcePath:(NSString *)sourcePath
                          destPath:(NSString *)destPath
                       targetWidth:(float)width
                      targerHeight:(float)height;

/**
 * 获取图片信息,并将图片信息写入到指定路径的文件中
 * @param sourcePath 原图片路径 eg:/Caches/aa.jpg
 * @param destPath 图片信息写入路径 eg:/Caches/aa_info.txt
 *
 */
-(void)im_acquireImageInfoWithSourcePath:(NSString *)sourcePath destPath:(NSString *)destPath;


@end
