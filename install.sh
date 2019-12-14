#! /bin/sh

sudo mkdir -pv /usr/local/lib
sudo cp -v build/libdbutil.so.1.0.1 /usr/local/lib/
sudo ln -sfv /usr/local/lib/libdbutil.so.1.0.1 /usr/local/lib/libdbutil.so.1
sudo ln -sfv /usr/local/lib/libdbutil.so.1.0.1 /usr/local/lib/libdbutil.so
sudo cp -rv src/*.h /usr/include
sudo ldconfig
