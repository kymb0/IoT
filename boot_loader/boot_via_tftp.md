#### boot embedded device via TFTP  
from u-boot console (prompt = `=>`):  
get adress range with `bdinfo` (we take note of DRAM bank start and size, we will load into this range)  
set address of tftp server:  
`setenv serverip <address>`  
Fetch the kernel, device tree blob file and root filesystem from tftp and store within memory range:  
`tftp 0x610000000 zImage`  
fetch DTB:  
`tftp 0x61a000000 vexpress-v2p-ca9.dtb`  
Fetch RootFS:  
`tftp 0x62000000000 rootfs.cpio.uboot`
Set kernel arguments:  
`setenv bootargs 'console=ttyAMA0 console=tty0 root=/dev/ram rw'`  
[.] Here:
```
- console=ttyAMA0: Redirect first serial port (on ARM architecture) to current session
- console=tty0: Redirect Qemu virtual serial port to current session
- root=/dev/ram: RAM device location
- rw : Mounting disk image in read/write mode
```
After these have all been set and loaded, we use bootz, specifying the locations of Kernel, RootFS and DTB:  
`bootz <address1> <address2> <address3>`
