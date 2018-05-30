#!/bin/sh

# cd to root directory
cd ..

# clean the demo install first
echo "=============================="
echo "Removing previous compilation"
echo "=============================="
make cleandemo OBJ_DIR=armobj

# make the demo with arm compiler
echo "=============================="
echo "Compiling demo for arm chipset"
echo "=============================="
# have to disable unused result warning for ev3dev system calls
# have to direct boost libraries to the location of the ARM cross compiled libraries
make demo CC=arm-linux-gnueabi-g++ CCFLAGS="-std=c++11 -O2 -Wno-unused-result -D_GLIBCXX_USE_NANOSLEEP -DEV3DEV_PLATFORM_EV3" LIBS="-L/usr/lib/arm-boost/lib -lboost_graph -lboost_program_options" OBJ_DIR=armobj

# NOTE:
# When moving the binary onto the ev3dev, also add the precompiled boost (.so) library files into the path
# A check to see if all required libaries are in the path can be done by doing "ldd" command