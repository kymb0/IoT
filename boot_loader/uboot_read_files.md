Say we have access to uboot console, and we want to read files.  
We can navigate the FS using `ext4ls` (this may change depending on the filesystem, use `help`)  
once you locate the file you want to read, `bdinfo` to view available memory address range  
load the file into memory `ext4load 0x62000000 /bin/flag 0x21` (remember to convert filesize to hex for last arg)  
read memory location `md 0x62`
