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

对于某些`Linux平台`需改用`libevent/linux/event2/event-config2.h`否则程序无法正常运行

交叉编译`macOS平台`请使用[osxcross](https://github.com/tpoechtrager/osxcross)

### 使用CMAKE编译
通用(Linux/macOS/Windows)
```
cd build
cmake ..
cmake --build . --config Release
```

使用NDK编译(Android)
```
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=${NDK_HOME}/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_TOOLCHAIN=clang
cmake --build . --config Release
```

构造64位(Windows)
```
cd build
cmake .. -A"x64"
cmake --build . --config Release
```

使用MinGW编译(推荐使用[clang](https://github.com/mstorsjo/llvm-mingw/releases/tag/20200325))
```
cd build
cmake .. -G"MinGW Makefiles"
cmake --build . --config Release
```
