#!/bin/bash
source /root/env.sh

cp archives/v4.20.tar.gz .
tar -xzf v4.20.tar.gz
cd linux-4.20
make vexpress_defconfig
./scripts/config -e CONFIG_BLK_DEV_RAM
./scripts/config --set-val BLK_DEV_RAM_SIZE 100000
./scripts/config -e CONFIG_DEVTMPFS_MOUNT
yes '' | make oldconfig
make -j8

if [ ! -d /root/output ]
then
        mkdir -p /root/output
fi
cp arch/arm/boot/dts/vexpress-v2p-ca9.dtb /root/output
cp arch/arm/boot/zImage /root/output

cd -
root@attackdefense:~# cat build_uboot.sh
#!/bin/bash
source /root/env.sh

cp archives/v2019.07.tar.gz .
tar -xzf v2019.07.tar.gz
cd u-boot-2019.07

make vexpress_ca9x4_defconfig
make -j8

if [ ! -d /root/output ]
then
        mkdir -p /root/output
fi
cp u-boot  /root/output

cd -
