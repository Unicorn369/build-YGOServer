#!/usr/bin/env bash
#OSX=: AR=x86_64-apple-darwin20.4-ar CC=x86_64-apple-darwin20.4-clang CXX=x86_64-apple-darwin20.4-clang++
cd android
rm -rf libs obj
ndk-build USR_SHARED=true -j3
cd ../linux
rm -rf bin obj
STRIP=strip make -j3
cd ../macosx
rm -rf bin obj
OSX make -j3
