#!/bin/bash
source /root/env.sh

cp archives/buildroot-2019.02.5.tar.gz .
tar -xzf buildroot-2019.02.5.tar.gz

cd buildroot-2019.02.5
mkdir vexpress_build
cp /root/vexpress_buildroot_config vexpress_build/.config

cp /root/archives/dl.tar.gz .
tar -xzfdl.tar.gz

make O=vexpress_build

if [ ! -d /root/output ]
then
        mkdir -p /root/output
fi
cp vexpress_build/images/rootfs.ext2 /root/output

cd -
