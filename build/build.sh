#!/usr/bin/env bash
cd android
rm -rf libs obj
ndk-build -j3
cd ../linux
rm -rf bin obj
make -j3
cd ../macosx
rm -rf bin obj
OSX make -j3
