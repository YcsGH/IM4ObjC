//
//  ycmagick.c
//  ImageMagick
//
//  Created by ycs on 17/3/8.
//  Copyright © 2017年 yuancore. All rights reserved.
//

#import <stdio.h>
#import <stdlib.h>
#import <string.h>

#import "ImageMagick.h"
#import "MagickWand.h"

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
int ycmagickthumnail(int argc,char **argv,float width,float height){
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
    IdentifyImage(image, targetFile, MagickTrue);
    fclose(targetFile);
    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
    
    return 0;
}





