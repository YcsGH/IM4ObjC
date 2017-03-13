//
//  ImageMagickEngine.h
//  IM4ObjC
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum : NSUInteger {
    ImageOptModeTypeZero,
    ImageOptModeTypeOne,
    ImageOptModeTypeTwo,
    ImageOptModeTypeThree,
    ImageOptModeTypeFour,
    ImageOptModeTypeFive,
} ImageOptModeType;//图片处理的各种模式

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
                       targetWidth:(int)width
                      targerHeight:(int)height;

/**
 * 获取图片信息,并将图片信息写入到指定路径的文件中
 * @param sourcePath 原图片路径 eg:/Caches/aa.jpg
 * @param destPath 图片信息写入路径 eg:/Caches/aa_info.txt
 *
 */
-(void)im_acquireImageInfoWithSourcePath:(NSString *)sourcePath destPath:(NSString *)destPath;

/**
 * 裁剪图片
 * @param sourcePath 原图片路径 eg:/Caches/aa.jpg
 * @param destPath 目标图片路径 eg:/Caches/aa.jpg
 * @param pointX 裁剪起点相对于原图片的X偏移量
 * @param pointY 裁剪起点相对于原图片的Y偏移量
 * @param width 目标图片长度
 * @param height 目标图片高度
 */
-(void)im_cropImageCutWithSourcePath:(NSString *)sourcePath
                            destPath:(NSString *)destPath
                              pointX:(int)pointX
                              pointY:(int)pointY
                               width:(int)width
                              height:(int)height;

/**
 * 多种模式处理图片
 * @param modeType 处理模式
 * @param sourcePath 原图片路径 eg:/Caches/aa.jpg
 * @param destPath 目标图片路径 eg:/Caches/aa_fix.jpg
 * @param width 目标图片长度,为0表示不指定
 * @param height 目标图片高度,为0表示不指定
 * @param quality 压缩程度(0~100)
 */
-(void)im_resizeImageWithMode:(ImageOptModeType)modeType
                   sourcePath:(NSString *)sourcePath
                     destPath:(NSString *)destPath
                        width:(int)width
                       height:(int)height
                      quality:(double)quality;


/*
 * `多种模式处理图片`的说明:
 *  
 模式0：限定缩略图的长边最多为 $LongEdge$，短边最多为$ShortEdge$，进行等比缩放，不裁剪。
 模式1：限定缩略图的宽最少为$Width$，高最少为$Height$，进行等比缩放，居中裁剪。转后的缩略图通常恰好是 $Width$x$Height$ 的大小（有一个边缩放的时候会因为超出矩形框而被裁剪掉多余部分）。如果只指定 w 参数或只指定 h 参数，代表限定为长宽相等的正方图。
 模式2：限定缩略图的宽最多为$Width$，高最多为$Height$，进行等比缩放，不裁剪。如果只指定 w 参数则表示限定宽（长自适应），只指定 h 参数则表示限定长（宽自适应）。它和模式0类似，区别只是限定宽和高，不是限定长边和短边。从应用场景来说，模式0适合移动设备上做缩略图，模式2适合PC上做缩略图。
 模式3:限定缩略图的宽最少为$Width$，高最少为$Height$，进行等比缩放，不裁剪。如果只指定 w 参数或只指定 h 参数，代表长宽限定为同样的值。你可以理解为模式1是模式3的结果再做居中裁剪得到的。
 模式4：限定缩略图的长边最少为$LongEdge$，短边最少为$shortEdge$，进行等比缩放，不裁剪。如果只指定 w 参数或只指定 h 参数，表示长边短边限定为同样的值。这个模式很适合在手持设备做图片的全屏查看（把这里的长边短边分别设为手机屏幕的分辨率即可），生成的图片尺寸刚好充满整个屏幕（某一个边可能会超出屏幕）。
 模式5：限定缩略图的长边最少为$LongEdge$，短边最少为$shortEdge$，进行等比缩放，居中裁剪。如果只指定 w 参数或只指定 h 参数，表示长边短边限定为同样的值。同上模式4，但超出限定的矩形部分会被裁剪。
 *
 */






@end
