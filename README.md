# IM4ObjC

[![CI Status](http://img.shields.io/travis/1214099793@qq.com/IM4ObjC.svg?style=flat)](https://travis-ci.org/1214099793@qq.com/IM4ObjC)
[![Version](https://img.shields.io/cocoapods/v/IM4ObjC.svg?style=flat)](http://cocoapods.org/pods/IM4ObjC)
[![License](https://img.shields.io/cocoapods/l/IM4ObjC.svg?style=flat)](http://cocoapods.org/pods/IM4ObjC)
[![Platform](https://img.shields.io/cocoapods/p/IM4ObjC.svg?style=flat)](http://cocoapods.org/pods/IM4ObjC)

## Installation
* 使用 lipo -create 命令生成framework静态库
* 将IM4ObjC.framework拖入到项目中.
* 添加依赖库libz.tbd libbz2.tbd libxml2.tbd
* 在Build Settings中搜索ENABLE_BITCODE,将Enable Bitcode设置为NO.

## Usage
ImageMagickEngine *imEngine = [[ImageMagickEngine alloc]init]; <br/>   [imEngine im_resizeImageWithMode:3 sourcePath:sourceImgPath destPath:destImgPath width:200 height:0 quality:0];

## Author

missL,ycs@yuancore.com

## License

IM4ObjC is available under the MIT license. See the LICENSE file for more info.

