#include <openssl/des.h>
#pragma once

#ifdef _WIN32
#ifdef __cplusplus
extern "C"
#endif
#endif
void
#ifdef _WIN32
__stdcall
#endif
MyDES(
	unsigned char	*pData,
	unsigned int	uLen,		// uLen == 7
	unsigned char	Hash[8]
);
void setup_des_key(unsigned char key_56[], DES_key_schedule &ks);
void HashNetNTLMv1(
	unsigned char	*pData,
	unsigned int	uLen,		// uLen == 7
	unsigned char	Hash[8]
);