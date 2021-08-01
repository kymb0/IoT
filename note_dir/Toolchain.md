#### Toolchain:
'software to build software', eg the 'hamer and drill to build furniture'
Consits of compiler, assembler, linker and other utils.

Come in two types: native and cross.
native: create apps for the current system
native: allows you to build software for other platforms via cross compilers etc.

toolchain naming conventions:
Architecture-vendor-kernel-runtime EG arm-buildroot-linux-uclibcgnueabihf

To build firmware, we need to build the toolchain.
