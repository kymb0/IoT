# This is the base directory for the entire course
export BASE_INSTALL_DIR=$PWD

export TOOL_CHAIN_PATH=$BASE_INSTALL_DIR/Step-1/customtoolchain

# setup toolchain in path (built with crosstool-NG in path)
export PATH=$PATH:$TOOL_CHAIN_PATH/bin:$TOOL_CHAIN_PATH/arm-unknown-linux-uclibcgnueabihf/bin

# create an alias for "make" with cross compilation toolchain options 

alias arm-make='ARCH=arm CROSS_COMPILE=arm-unknown-linux-uclibcgnueabihf- make'
