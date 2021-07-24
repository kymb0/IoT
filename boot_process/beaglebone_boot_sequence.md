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
