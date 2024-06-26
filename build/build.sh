#!/usr/bin/env bash
#OSX=: AR=x86_64-apple-darwin20.4-ar CC=x86_64-apple-darwin20.4-clang CXX=x86_64-apple-darwin20.4-clang++
cd android
rm -rf libs obj
ndk-build -j3
cd ../linux
rm -rf bin obj
make -j3
strip bin/Release/AI.Server.linux
cd ../macosx
rm -rf bin obj
OSX make -j3
