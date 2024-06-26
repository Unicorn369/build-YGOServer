# build-YGOServer
用于 [YGOPro2](https://github.com/Unicorn369/YGOPro2) 人机对战服务

支持的平台：

`Android |
arm64-v8a
armeabi-v7a
x86
`

`Linux |
x64
`

`macOS |
arm64
x86_64
`

`Windows |
x86
x86_64
` 

# 编译说明
编译请参考`build/build.bat`或`build/build.sh`

对于某些`Linux平台`需改用`libevent/linux/event2/event-config2.h`否则程序无法正常运行

交叉编译`macOS平台`请使用[osxcross](https://github.com/tpoechtrager/osxcross)
