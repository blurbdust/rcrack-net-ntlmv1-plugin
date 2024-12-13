set LIB=C:\Program Files\OpenSSL-Win64\lib;%LIB%
set INCLUDE=C:\Program Files\OpenSSL-Win64\include;%INCLUDE%


cl /LD /O2 alglib1.c MD5.c /EXPORT:HashAlgorithms

@del *.obj
@del *.exp
@del *.lib
