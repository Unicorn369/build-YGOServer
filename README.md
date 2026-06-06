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

## 如何编译
编译请参考`build/build.bat`或`build/build.sh`

编译Linux平台推荐使用 [musl编译器](https://github.com/Unicorn369/build-YGOServer/releases/tag/v0.0.0) 防止在其他Linux上因glib版本问题不能运行

在Linux平台上，交叉编译`macOS`与`windows`请使用此工具 --> [tools](https://github.com/Unicorn369/build-YGOServer/releases/tag/v0.0.0)
