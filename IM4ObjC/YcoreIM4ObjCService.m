//
//  YcoreIM4ObjCService.m
//  Temproject
//
//  Created by ycs on 17/3/4.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import "YcoreIM4ObjCService.h"
#import <MagickWand.h>

typedef struct _CommandParameter {
    int argc;
    char** argv;
    float width;
    float height;
} CommandParameter;//多元组类型用结构体代替

int ycmagicktransformat(int argc, char **argv);//图片格式转换
int ycmagickthumnail(int argc,char **argv,float width,float height);//缩略图
int ycacquireimageinfo(int argc,char** argv);//获取图片信息

////////////////////////////////////////////////////////////////////////
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

CommandParameter buildCmdParameterV1(NSString* command,float width,float height,NSString* sourcepath,NSString *destpath){
    CommandParameter commandParameter;
    commandParameter = buildCmdParameter(command, sourcepath, destpath);
    commandParameter.width = width;
    commandParameter.height = height;
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
                       targetWidth:(float)width
                      targerHeight:(float)height {
    CommandParameter cmd = buildCmdParameterV1(@"magick", width, height, sourcePath, destPath);
    int ret = ycmagickthumnail(cmd.argc, cmd.argv, cmd.width, cmd.height);
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












@end
