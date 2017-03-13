//
//  ycmagick.c
//  IM4ObjC
//
//  Created by ycs on 17/3/8.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import <stdio.h>
#import <stdlib.h>
#import <string.h>

#import <magick/ImageMagick.h>
#import <wand/MagickWand.h>

/* 图片格式转换 */
int ycmagicktransformat(int argc, char **argv) {
    MagickWand *magick_wand;
    MagickBooleanType status;
    
    /* read an image */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) { //读取图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    /* write the image */
    MagickResetIterator(magick_wand);
    while (MagickNextImage(magick_wand) != MagickFalse) {
        status = MagickWriteImage(magick_wand, argv[2]);
        if (status == MagickFalse) { //写图片失败
            magick_wand = DestroyMagickWand(magick_wand);
            MagickWandTerminus();
            return -1;
        }
        
    }
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}

/* 获取指定宽高的缩略图 */
int ycmagickthumnail(int argc,char **argv,int width,int height,double quality){
    MagickBooleanType status;
    MagickWand *magick_wand;
    /*
     Read an image.
     */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand,argv[1]);
    if (status == MagickFalse){
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    status = MagickSetCompressionQuality(magick_wand, quality);
    if (status == MagickFalse){
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    /*
     Turn the images into a thumbnail sequence.
     */
    MagickResetIterator(magick_wand);
    while (MagickNextImage(magick_wand) != MagickFalse)
        MagickResizeImage(magick_wand,width,height,LanczosFilter,1.0);
    /*
     Write the image then destroy it.
     */
    status = MagickWriteImages(magick_wand,argv[2],MagickTrue);
    if (status == MagickFalse){
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}

/* 获取图片信息,写入到指定文件中 */
int ycacquireimageinfo(int argc,char** argv){
    MagickWand *magick_wand;
    MagickBooleanType status;
    
    /* read an image */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) { //读取图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    Image *image = GetImageFromMagickWand(magick_wand);
    FILE *targetFile = fopen(argv[2], "w+");//若文件不存在,则创建文件
    status = IdentifyImage(image, targetFile, MagickTrue);
    fclose(targetFile);
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    if (targetFile == NULL || status == MagickFalse) {
        return -1;
    }
    
    return 0;
}

/* 图片裁剪 */
int ycimagecut(int argc,char** argv,int pointX,int pointY,int width,int height){
    MagickWand *magick_wand;
    MagickBooleanType status;
    
    /* read an image */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) { //读取图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    status = MagickCropImage(magick_wand, width, height, pointX, pointY);
    if (status == MagickFalse) { //裁剪图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    status = MagickWriteImage(magick_wand, argv[2]);
    if (status == MagickFalse) { //写图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}

/* 构建命令行参数 */

char** buildCmdPramsV0(int version,char** argv,int width,int height,double quality) { // char** 字符串数组
    char sizee[1024],qualitys[10];
    sprintf(qualitys, "%f",quality);
    if (version == 0) {
        sprintf(sizee,"%dx%d",width,height);
    }
    else if (version == 1){
        sprintf(sizee, "%d",width);
    }
    else if (version == 2){
        sprintf(sizee, "x%d",width);
    }
    char *args[] = {"convert",argv[1],"-resize",sizee,"-quality",qualitys,argv[2],NULL};
    char** temp = (char**)malloc(sizeof(char*)*8);
    int i;
    for(i = 0;i < 7; i++){
        temp[i]=(char*)malloc(sizeof(char)*1024);
        strcpy(temp[i],args[i]);
    }
    *(temp + i) = NULL;/* 确保参数正确 */
    return temp;
}

char** buildCmdPramsV1(int version,char** argv,int width,int height,double quality) { // char** 字符串数组
    char sizee[50],qualitys[10],rect[50];
    sprintf(qualitys, "%f",quality);
    if (version == 3) {
        sprintf(sizee,"%dx%d^",width,height);
        sprintf(rect, "%dx%d",width,height);
    }
    char *args[] = {"convert",argv[1],"-resize",sizee,"-gravity","center","-extent",rect,"-quality",qualitys,argv[2],NULL};
    char** temp = (char**)malloc(sizeof(char*)*12);
    int i;
    for(i = 0;i < 11; i++){
        temp[i]=(char*)malloc(sizeof(char)*1024);
        strcpy(temp[i],args[i]);
    }
    *(temp + i) = NULL;/* 确保参数正确 */
    return temp;
}

char** buildCmdPramsV2(int version,char** argv,int width,int height,double quality) { // char** 字符串数组
    char sizee[50],qualitys[10];
    sprintf(qualitys, "%f",quality);
    if (version == 4) {
        sprintf(sizee,"%dx%d^",width,height);
    }
    char *args[] = {"convert",argv[1],"-resize",sizee,"-quality",qualitys,argv[2],NULL};
    char** temp = (char**)malloc(sizeof(char*)*8);
    int i;
    for(i = 0;i < 7; i++){
        temp[i]=(char*)malloc(sizeof(char)*1024);
        strcpy(temp[i],args[i]);
    }
    *(temp + i) = NULL;/* 确保参数正确 */
    return temp;
}


/* 图片处理,调用命令行 */
int ycmagickresize(int version,char** argv,int width,int height,double quality){
    MagickCoreGenesis(argv[0],MagickFalse);
    MagickStatusType status;
    ImageInfo *image_info;
    ExceptionInfo *exception = AcquireExceptionInfo();
    image_info = AcquireImageInfo();
    int arg_count;
    char** args;
    if (version >= 0 && version < 3) {
        args = buildCmdPramsV0(version,argv,width,height,quality);
    }else if (version == 3 ){
        args = buildCmdPramsV1(version,argv,width,height,quality);
    }
    else if (version == 4){
        args = buildCmdPramsV2(version,argv,width,height,quality);
    }
    
    for(arg_count = 0; args[arg_count] != (char *)NULL; arg_count++);
    status = ConvertImageCommand(image_info, arg_count, args, NULL, exception);
    for (int i = 0; i<arg_count+1; i++) {
        free(args[i]);
    }
    free(args);
    if (exception->severity != UndefinedException){
        printf("%s\n",exception->description);
        image_info=DestroyImageInfo(image_info);
        exception=DestroyExceptionInfo(exception);
        MagickCoreTerminus();
        return -1;
    }
    image_info=DestroyImageInfo(image_info);
    exception=DestroyExceptionInfo(exception);
    MagickCoreTerminus();
    return 0;
}

/////////////////////////// 图片各种模式的处理 ///////////////////////////////

/**
 * 长边最多为<LongEdge>，短边最多为<ShortEdge>，进行等比缩放，不裁剪
 */
int ycresize_mod0(int argc,char **argv,int width,int height,double quality){
    MagickWand *magick_wand;
    MagickBooleanType status;
    
    /* read an image */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) { //读取图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    int w = (int)MagickGetImageWidth(magick_wand);
    int h = (int)MagickGetImageHeight(magick_wand);
    int LongEdgeTmp = width;
    int ShortEdgeTmp = height;
    
    /* 3种情况 */
    if (width > 0 && height > 0) {
        if ((w > h && LongEdgeTmp < ShortEdgeTmp) || (w < h && LongEdgeTmp > ShortEdgeTmp)) {
            int temp = LongEdgeTmp;
            LongEdgeTmp = ShortEdgeTmp;
            ShortEdgeTmp = temp;
        }
        return ycmagickresize(0, argv, LongEdgeTmp, ShortEdgeTmp, quality);
    }
    else if (width > 0 && height == 0){
        if (w > h) {
            return ycmagickresize(1, argv, LongEdgeTmp, ShortEdgeTmp, quality);
        }else{
            return ycmagickresize(2, argv, LongEdgeTmp, ShortEdgeTmp, quality);
        }
    }
    else if(width == 0 && height > 0){
        if (w < h) {
            return ycmagickresize(1, argv, ShortEdgeTmp, LongEdgeTmp, quality);
        }else{
            return ycmagickresize(2, argv, ShortEdgeTmp, LongEdgeTmp, quality);

        }
    }
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}


/**
 * 宽最少为<Width>，高最少为<Height>，进行等比缩放，居中裁剪。
 */
int ycresize_mod1(int argc,char **argv,int width,int height,double quality){
    if (width > 0 && height > 0) {
        return ycmagickresize(3, argv, width, height, quality);
    }else if (width > 0 && height == 0){
        return ycmagickresize(3, argv, width, width, quality);
    }else if(width == 0 && height > 0){
        return ycmagickresize(3, argv, height, height, quality);
    }
    return 0;
}

/**
 * 宽最多为<Width>，高最多为<Height>，进行等比缩放，不裁剪
 */
int ycresize_mod2(int argc,char **argv,int width,int height,double quality){
    if (width > 0 && height > 0) {
        return ycmagickresize(0, argv, width, height, quality);
    }else if (width > 0 && height == 0){
        return ycmagickresize(1, argv, width, height, quality);
    }else if(width == 0 && height > 0){
        return ycmagickresize(2, argv, height, height, quality);
    }
    return 0;
}

/**
 * 宽最少为<Width>，高最少为<Height>，进行等比缩放，不裁剪
 */
int ycresize_mod3(int argc,char **argv,int width,int height,double quality){
    if (width > 0 && height > 0) {
        return ycmagickresize(4, argv, width, height, quality);
    }else if (width > 0 && height == 0){
        return ycmagickresize(4, argv, width, width, quality);
    }else if(width == 0 && height > 0){
        return ycmagickresize(4, argv, height, height, quality);
    }
    return 0;
}

/**
 * 长边最少为<LongEdge>，短边最少为<ShortEdge>，进行等比缩放，不裁剪
 */
int ycresize_mod4(int argc,char **argv,int width,int height,double quality){
    MagickWand *magick_wand;
    MagickBooleanType status;
    
    /* read an image */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) { //读取图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    int w = (int)MagickGetImageWidth(magick_wand);
    int h = (int)MagickGetImageHeight(magick_wand);
    int LongEdgeTmp = width;
    int ShortEdgeTmp = height;
    
    /* 3种情况 */
    if (width > 0 && height > 0) {
        if ((w > h && LongEdgeTmp < ShortEdgeTmp) || (w < h && LongEdgeTmp > ShortEdgeTmp)) {
            int temp = LongEdgeTmp;
            LongEdgeTmp = ShortEdgeTmp;
            ShortEdgeTmp = temp;
        }
        return ycmagickresize(4, argv, LongEdgeTmp, ShortEdgeTmp, quality);
    }
    else if (width > 0 && height == 0){
        return ycmagickresize(4, argv, LongEdgeTmp, LongEdgeTmp, quality);
    }
    else if(width == 0 && height > 0){
        return ycmagickresize(4, argv, ShortEdgeTmp, ShortEdgeTmp, quality);
    }
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}

/**
 * 长边最少为<LongEdge>，短边最少为<ShortEdge>，进行等比缩放，居中裁剪。
 */
int ycresize_mod5(int argc,char **argv,int width,int height,double quality){
    MagickWand *magick_wand;
    MagickBooleanType status;
    
    /* read an image */
    MagickWandGenesis();
    magick_wand = NewMagickWand();
    status = MagickReadImage(magick_wand, argv[1]);
    if (status == MagickFalse) { //读取图片失败
        magick_wand = DestroyMagickWand(magick_wand);
        MagickWandTerminus();
        return -1;
    }
    
    int w = (int)MagickGetImageWidth(magick_wand);
    int h = (int)MagickGetImageHeight(magick_wand);
    int LongEdgeTmp = width;
    int ShortEdgeTmp = height;
    
    /* 3种情况 */
    if (width > 0 && height > 0) {
        if ((w > h && LongEdgeTmp < ShortEdgeTmp) || (w < h && LongEdgeTmp > ShortEdgeTmp)) {
            int temp = LongEdgeTmp;
            LongEdgeTmp = ShortEdgeTmp;
            ShortEdgeTmp = temp;
        }
        return ycmagickresize(3, argv, LongEdgeTmp, ShortEdgeTmp, quality);
    }
    else if (width > 0 && height == 0){
        return ycmagickresize(3, argv, LongEdgeTmp, LongEdgeTmp, quality);
    }
    else if(width == 0 && height > 0){
        return ycmagickresize(3, argv, ShortEdgeTmp, ShortEdgeTmp, quality);
    }
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    return 0;
}
















