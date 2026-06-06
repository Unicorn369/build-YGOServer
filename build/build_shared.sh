#!/usr/bin/env bash
#MUSL=: AR=x86_64-linux-musl-ar CC=x86_64-linux-musl-cc CXX=x86_64-linux-musl-c++ STRIP=x86_64-linux-musl-strip
#OSX=: AR=x86_64-apple-darwin20.4-ar CC=x86_64-apple-darwin20.4-clang CXX=x86_64-apple-darwin20.4-clang++
#WIN=: AR=i686-w64-mingw32-ar CC=i686-w64-mingw32-clang CXX=i686-w64-mingw32-clang++ STRIP=i686-w64-mingw32-strip RESCOMP=i686-w64-mingw32-windres
cd android
rm -rf libs obj
ndk-build USR_SHARED=true -j$(grep -c "processor" /proc/cpuinfo)
cd ../linux.shared
rm -rf bin obj
MUSL make -j$(grep -c "processor" /proc/cpuinfo)
cd ../macosx.shared
rm -rf bin obj
OSX make -j$(grep -c "processor" /proc/cpuinfo)
cd ../mingw.shared
rm -rf bin obj
WIN make -j$(grep -c "processor" /proc/cpuinfo)
