// Simple Hello World in ARM Assembly 
// arm/EABI  syscall number in r7  r0-r6 contain arguments
// call "swi 0x0" to invoke syscall 
// More info:  http://man7.org/linux/man-pages/man2/syscall.2.html


.text

.globl _start


_start:

    // write() syscall 

    mov     %r0, $1             // stdout 
    ldr     %r1, =msg           // string 
    mov     %r2, $msg_len       // string len 
    mov     %r7, $4             // syscall number for write
    swi     $0                  // invoke syscall 


   // call exit() to gracefully exit the program 

    mov     %r0, $5             // return value for exit (putting 5 )  
    mov     %r7, $1             // syscall number for exit 
    swi     $0                  // invoke syscall 

.data

  // our string to print in the data section 

msg:
    .ascii      "How small am I?\n"
msg_len = . - msg
