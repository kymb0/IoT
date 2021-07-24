## understanding the boot process of an embedded device  

FSB = First Stage Bootloader  
SSB = Second Stage Bootloader
(There may not be 2 bootloaders, there could just be 1 stage, or multiple - this depends on the Architecture)
"Passes Control != "calling" - what is the difference? When control is passed, after this the previous program ceases to exist, whereas when you call, you return to the previous program. AKA once the SSB has finished, the bootloader will not run again until the next reset.

Important to know about: The SoC (system on Chip)/Microcontroller AKA the "brains" of the system, requires persistent storage, such as flash storage, to store the operating system can be stored across reboot
also requires RAM to load programs at runtime.  
Aside from these they may be dozens of different additional ports, but NOTE that they may not contain enough pins to connect to each device they support.  

### Stage 1, 2, and 3:
#### Bootloaders
When the board is powered, control is passed to a location called "reset vector" which is pre-programmed onto the board.
Typically the SoC bootrom loader will exist here, and start executing.
The SOC bootrom loader function is to load basic hardware, and then finding the FSB from a boot device (could be tftp, SD card, usb etc)

Once it has located the FSB, it will load it into the SoC's internal memory, and then pass control to it.  

The FSB will then fetch the SSB which will be then loaded into RAM, the FSB then passes control to the SSB, which then starts running.  

### Stage 4: Linux Kernel Device Tree File
SSB load kernel and device tree into RAM and look at it's own settings (either statically embedded or config file).  Then use these to start the kernel and pass it the boot args. After this the SSB ceases to exist, and the Linux kernel takes over.

#### Stage 5: Root Filesystem Init Process
The kernel initializes hardware components, look into boot args, locate rootFS and mount it. 

Then search for the init process on the FS, which is the first userspace proc with PID 0. After it invokes the init proc, init will look at its config files and start other userspace processes.

