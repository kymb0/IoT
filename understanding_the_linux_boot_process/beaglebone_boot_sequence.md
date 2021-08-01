#### System start-up
&#8595;
#### initialization : SoC romcode executes
&#8595;
#### __main() (stack setup)
&#8595;
#### main()
&#8595;
#### MPU WDT 1 setup : setup watchdog timer, gives rom bootloader code 3 minutes to find booot device and load next stage
 &#8595;
#### DPLLs and clocks configs
&#8595;
#### booting : rom bootloader will try and see how it can boot the next stage.  

Where is the next stage? it is external to the SoC.  
So how does the rom boot loader find the next stage?  
The order in which in which it searches for a boot device is determined by the boot-pin configuration as designed by the hardware architects.  
For each device it searches through, determine if it is a peripheral boot or memory boot.  
Lets assume now that we are booting from MMC/SD. (memory boot)  
The rom bootloader will initialize the driver, and then decide if the next stage bootloader is on the SD card in rom mode or as a boot file.  

There are two modes in which it can do this:  
RAW mode:
this is where we put the next stage bootloader in memory - the filename is MLO. 

FAT mode:  
Read from a FAT partition on the SD card

### An example of how this flows with BeagleBone Black Boot Process:  
MMC/SD contains: MLO+U-Boot+uEnv.txt on a fat32 partition (First stage bootloader), the Linux Kernel + Device Tree Binary (enumeration of non-discoverable devices, how to connect them etc) on a ext4 partition, and the root flesystem on another ext4 partition. We partition them like to make it easier to quickly change our kernel and configs.  

First, SoC is powered up (reset vector initialised), ROM bootloader finds MMC/SD with a fat32 partition with MLO file and loads it into Internal RAM, and passes control to it.  
From here the MLO sends U-Boot to RAM, from here U-Boot then checks if uEnv.txt is present and copies that to RAM.  
U-Boot then checks for ext4 partitions by looking at uEnv.txt, then fetches the Kernel and DSB and loads them into RAM, then sends boot args and passes control to Kernel which will mount rootfs, and run init process from rootfs in RAM, Init process then starts user space programs.  


"Why do we need MLO, why cant ROM bootloader simply grab the kernel?"  
Simply, cost.  
RAM space in a SoC is cost-prohibitive, and UBoot is too large to fit in 176kb.  
"Why can't it load Uboot directly onto ram, if MLO is simply loading it into Ram?"  
Simply because the ROM bootlaoder does not know enough about our system, and as such we require the MLO file to feed it the info it needs to succesfully move uboot across.  

![Boot Process Slide](https://github.com/kymb0/IoT/raw/main/images/BeagleBone_Boot.png)
