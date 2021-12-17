#!/bin/sh


if ! [ -d build]; then
    mkdir build
fi


cd build

make -j$(nproc)

cd ../RunTree

./../build/3D