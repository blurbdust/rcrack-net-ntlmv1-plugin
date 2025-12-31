set LIB=C:\Program Files\OpenSSL-Win64\lib\VC\x64\MT;%LIB%
set INCLUDE=C:\Program Files\OpenSSL-Win64\include;%INCLUDE%


cl /LD /O2 alglib1.cpp DES.cpp /link /EXPORT:HashAlgorithms

@del *.obj
@del *.exp
@del *.lib
