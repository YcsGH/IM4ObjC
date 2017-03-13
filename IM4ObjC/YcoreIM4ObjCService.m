//
//  YcoreIM4ObjCService.m
//  IM4ObjC
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import "YcoreIM4ObjCService.h"
#import <wand/MagickWand.h>

typedef struct _CommandParameter {
    int argc;
    char** argv;
    int width;
    int height;
    int pointX;
    int pointY;
}CommandParameter;//多元组类型用结构体代替

#pragma mark ====== C API ======
int ycmagicktransformat(int argc, char **argv);//图片格式转换
int ycmagickthumnail(int argc,char **argv,int width,int height,double quality);//缩略图
int ycacquireimageinfo(int argc,char** argv);//获取图片信息
int ycimagecut(int argc,char** argv,int pointX,int pointY,int width,int height);//图片裁剪
int ycresize_mod0(int argc,char **argv,int width,int height,double quality);//模式0
int ycresize_mod1(int argc,char **argv,int width,int height,double quality);//模式1
int ycresize_mod2(int argc,char **argv,int width,int height,double quality);//模式2
int ycresize_mod3(int argc,char **argv,int width,int height,double quality);//模式3
int ycresize_mod4(int argc,char **argv,int width,int height,double quality);//模式4
int ycresize_mod5(int argc,char **argv,int width,int height,double quality);//模式5

#pragma mark ====== 命令行参数构建 ======
CommandParameter buildCmdParameter(NSString* command,NSString* sourcepath,NSString *destpath){
    CommandParameter commandParameter;
    NSMutableString *cmd = [NSMutableString string];
    [cmd appendString:command];
    if (sourcepath == nil){
        NSLog(@"原图片路径不存在!");
        sourcepath = @"";
    }
    [cmd appendString:@" "];//不要忘记加空格
    [cmd appendString:sourcepath];
    if (destpath == nil) {
        NSLog(@"目标图片路径不存在!");
        destpath = @"";
    }
    [cmd appendString:@" "];
    [cmd appendString:destpath];
    
    NSArray *cmds = [cmd componentsSeparatedByString:@" "];
    int argc = (int)cmds.count;
    char** argv = (char**)malloc(sizeof(char*)*argc);
    for(int i = 0;i < argc; i++){
        argv[i]=(char*)malloc(sizeof(char)*1024);
        strcpy(argv[i],[[cmds objectAtIndex:i] UTF8String]);
    }
    commandParameter.argc = argc;
    commandParameter.argv = argv;
    return commandParameter;
}

CommandParameter buildCmdParameterV1(NSString* command,int width,int height,NSString* sourcepath,NSString *destpath){
    CommandParameter commandParameter;
    commandParameter = buildCmdParameter(command, sourcepath, destpath);
    commandParameter.width = width;
    commandParameter.height = height;
    return commandParameter;
}

CommandParameter buildCmdParameterV2(NSString* command,int pointX,int pointY,int width,int height,NSString* sourcepath,NSString *destpath){
    CommandParameter commandParameter;
    commandParameter = buildCmdParameterV1(command, width, height, sourcepath, destpath);
    commandParameter.pointX = pointX;
    commandParameter.pointY = pointY;
    return commandParameter;
}

void cleanCmdParameter(CommandParameter cmdParameter){
    int argc = cmdParameter.argc;
    char** argv = cmdParameter.argv;
    for (int i=0; i<argc; i++) {
        free(argv[i]);// argv 与 *argv 是两个不同的指针
    }
    free(argv);
}

@implementation YcoreIM4ObjCService


#pragma mark ====== 图片格式转换 ======

-(void)transformatWithSourcePath:(NSString *)sourcePath
                        destPath:(NSString *)destPath {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameter(@"magick", sourcePath,destPath);
    int ret = ycmagicktransformat(cmd.argc, cmd.argv);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);
}

#pragma mark ====== 获取指定宽高的图片 ======
-(void)thumnailImageWithSourcePath:(NSString *)sourcePath
                          destPath:(NSString *)destPath
                       targetWidth:(int)width
                      targerHeight:(int)height {
    CommandParameter cmd = buildCmdParameterV1(@"magick", width, height, sourcePath, destPath);
    int ret = ycmagickthumnail(cmd.argc, cmd.argv, cmd.width, cmd.height,0);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);
}

#pragma mark ====== 获取图片信息 ======
-(void)acquireImageInfoWithSourcePath:(NSString *)sourcePath
                             destPath:(NSString *)destPath{
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameter(@"identify", sourcePath,destPath);
    int ret = ycacquireimageinfo(cmd.argc, cmd.argv);
    if (ret == 0) {
        printf("恭喜哈,图片信息写入成功\n");
    }else{
        printf("很遗憾,图片信息写入失败!\n");
    }
    cleanCmdParameter(cmd);
}

#pragma mark ====== 图片裁剪 ======
-(void)cropImageCutWithSourcePath:(NSString *)sourcePath
                         destPath:(NSString *)destPath
                           pointX:(int)pointX
                           pointY:(int)pointY
                            width:(int)width
                           height:(int)height {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV2(@"crop", pointX, pointY, width, height, sourcePath, destPath);
    int ret = ycimagecut(cmd.argc, cmd.argv, cmd.pointX, cmd.pointY, cmd.width, cmd.height);
    if (ret == 0) {
        printf("恭喜哈,图片裁剪成功\n");
    }else{
        printf("很遗憾,图片裁剪失败!\n");
    }
    cleanCmdParameter(cmd);
}

#pragma mark ====== 图片处理.多种模式 ======

-(void)resizeImageWithMode:(ImageOptModeType)modeType
                sourcePath:(NSString *)sourcePath
                  destPath:(NSString *)destPath
                     width:(int)width
                    height:(int)height
                   quality:(double)quality {
    switch (modeType) {
        case ImageOptModeTypeZero:
            [self resizeMod0:sourcePath destPath:destPath width:width height:height quality:quality];
            break;
        case ImageOptModeTypeOne:
            [self resizeMod1:sourcePath destPath:destPath width:width height:height quality:quality];
            break;
        case ImageOptModeTypeTwo:
            [self resizeMod2:sourcePath destPath:destPath width:width height:height quality:quality];
            break;
        case ImageOptModeTypeThree:
            [self resizeMod3:sourcePath destPath:destPath width:width height:height quality:quality];
            break;
        case ImageOptModeTypeFour:
            [self resizeMod4:sourcePath destPath:destPath width:width height:height quality:quality];
            break;
        case ImageOptModeTypeFive:
            [self resizeMod5:sourcePath destPath:destPath width:width height:height quality:quality];
            break;
        default:
            break;
    }
}

/* 六种模式 */

// 限定缩略图的长边最多为 $LongEdge$，短边最多为 $ShortEdge$，进行等比缩放，不裁剪
-(void)resizeMod0:(NSString *)sourcePath
         destPath:(NSString *)destPath
            width:(int)width
           height:(int)height
          quality:(double)quality {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV1(@"convert", width, height, sourcePath, destPath);
    int ret = ycresize_mod0(3, cmd.argv, width, height, quality);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);
}

//
-(void)resizeMod1:(NSString *)sourcePath
         destPath:(NSString *)destPath
            width:(int)width
           height:(int)height
          quality:(double)quality {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV1(@"convert", width, height, sourcePath, destPath);
    int ret = ycresize_mod1(3, cmd.argv, width, height, quality);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);
}

-(void)resizeMod2:(NSString *)sourcePath
         destPath:(NSString *)destPath
            width:(int)width
           height:(int)height
          quality:(double)quality {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV1(@"convert", width, height, sourcePath, destPath);
    int ret = ycresize_mod2(3, cmd.argv, width, height, quality);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);
}

-(void)resizeMod3:(NSString *)sourcePath
         destPath:(NSString *)destPath
            width:(int)width
           height:(int)height
          quality:(double)quality {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV1(@"convert", width, height, sourcePath, destPath);
    int ret = ycresize_mod3(3, cmd.argv, width, height, quality);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);

}

-(void)resizeMod4:(NSString *)sourcePath
         destPath:(NSString *)destPath
            width:(int)width
           height:(int)height
          quality:(double)quality {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV1(@"convert", width, height, sourcePath, destPath);
    int ret = ycresize_mod4(3, cmd.argv, width, height, quality);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);

}

-(void)resizeMod5:(NSString *)sourcePath
         destPath:(NSString *)destPath
            width:(int)width
           height:(int)height
          quality:(double)quality {
    printf("%s\n",[destPath UTF8String]);
    CommandParameter cmd = buildCmdParameterV1(@"convert", width, height, sourcePath, destPath);
    int ret = ycresize_mod5(3, cmd.argv, width, height, quality);
    if (ret == 0) {
        printf("恭喜哈,图片转换成功\n");
    }else{
        printf("很遗憾,图片转换失败!\n");
    }
    cleanCmdParameter(cmd);

}


@end
