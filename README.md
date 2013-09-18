PKCS12toPEM
===========

Statically links to openssl to create a win32 DLL that can be used to convert a PKCS12 (PFX) file to a PEM file.


The DLL was originally built against openssl-1.0.1e, which was compiled using VC++2010:
Configure with platform VC-WIN32:

 > perl Configure VC-WIN32 --prefix=c:\some\openssl\dir

 Where the prefix argument specifies where OpenSSL will be installed to.

 Next you need to build the Makefiles and optionally the assembly
 language files:

 - If you are using NASM then run, like I did when compiling for PKCS12toPEM:

   > ms\do_nasm

 - If you don't want to use the assembly language files at all then run:

   > perl Configure VC-WIN32 no-asm --prefix=c:/some/openssl/dir
   > ms\do_ms

 Then from the VC++ environment at a prompt do:

 > nmake -f ms\nt.mak

 > nmake -f ms\nt.mak test

 > nmake -f ms\nt.mak install

 Tweaks:
 By default the library is not compiled with debugging
 symbols. If you use the platform debug-VC-WIN32 instead of VC-WIN32
 then debugging symbols will be compiled in.


