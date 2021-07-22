#### bootloader  
we start by emulating a device with qemu:  
`qemu-system-arm -m 256 -M vexpress-a9 -nographic -kernel u-boot`  
what are doing here? `-m 256 `: Memory to be allocated to virtual device  
`-M vexpress-a9`: Virtual machine selection  
`-nographic` : To invoke qemu from CLI  
`-kernel u-boot` : Passing u-boot file to start booting from  

To boot device and explore image FS:  
`qemu-system-arm -m 256 -M vexpress-a9 -nographic -kernel vmlinuz-3.2.0-4-vexpress -initrd initrd.img-3.2.0-4-vexpress -drive if=sd,file=debian_wheezy_armhf_standard.qcow2 -append "root=/dev/mmcblk0p2 rw console=ttyAMA0"`  

`-m 256` : Memory to be allocated to virtual device  
`-M vexpress-a9`: Virtual machine selection  
`-nographic` : To invoke qemu from CLI  
`-kernel vmlinuz-3.2.0-4-vexpress`: Linux kernel image to use  
`-initrd initrd.img-3.2.0-4-vexpress`: Initial RAM image to use  
`-drive if=sd,file=debian_wheezy_armhf_standard.qcow2` : disk image to be mounted as
SD card  
`-append` : to define Boot parameters  
`- root=/dev/mmcblk0p2` : Filesystem location i.e. 2nd partition (p2) of mounted SD card  
`- rw` : Mounting SD card in read/write mode  
`- console=ttyAMA0` : Direct console output to current shell session  


Scenario: uboot fails to find location of kernel.  
Solution: list available devices: `mmc list`, list contents of device: `ext2ls mmc 0:1`  
here:  
```
- mmc : Device type
- 0 : Device number
- 1 : Partition number
```
get board info: `bdinfo`  
Load kernel and Device Tree Blob file to valid memory addresses - make sure that
they don’t overwrite each other.  
Set kernel parameters:  
`setenv bootargs 'console=ttyAMA0 console=tty0 root=/dev/mmcblk0p1 rw'`
