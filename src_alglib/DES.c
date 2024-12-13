
#include "DES.h"
#ifdef _WIN32
#pragma comment(lib, "libeay32.lib")
#endif

void
#ifdef _WIN32
__stdcall
#endif
MyDES(
	unsigned char	*pData,
	unsigned int	uLen,		// uLen == 7
	unsigned char	Hash[8])
{

	// DES-ECB(expanded_key1, "1122334455667788") == Net-NTLMv1[:8]
	// DES-ECB(expanded_key2, "1122334455667788") == Net-NTLMv1[8:16]

	DES_cblock input_data = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
	DES_key_schedule SchKey1;

	DES_cblock expanded_key1;

	// I'm hoping single byte lookups are faster than constantly accessing the input array
	char byte0, byte1, byte2, byte3, byte4, byte5, byte6, byte7;

	byte0 = pData[0];
	byte1 = pData[1];
	byte2 = pData[2];
	byte3 = pData[3];
	byte4 = pData[4];
	byte5 = pData[5];
	byte6 = pData[6];

	expanded_key1[0] = (					   ((byte0 >> 1) & 0x7f)  << 1);
	expanded_key1[1] = (((byte0 & 0x01) << 6 | ((byte1 >> 2) & 0x3f)) << 1);
	expanded_key1[2] = (((byte1 & 0x03) << 5 | ((byte2 >> 3) & 0x1f)) << 1);
	expanded_key1[3] = (((byte2 & 0x07) << 4 | ((byte3 >> 4) & 0x0f)) << 1);
	expanded_key1[4] = (((byte3 & 0x0f) << 3 | ((byte4 >> 5) & 0x07)) << 1);
	expanded_key1[5] = (((byte4 & 0x1f) << 2 | ((byte5 >> 6) & 0x03)) << 1);
	expanded_key1[6] = (((byte5 & 0x3f) << 1 | ((byte6 >> 7) & 0x01)) << 1);
	expanded_key1[7] = ( (byte6 & 0x7f) << 1);

	DES_cblock cipher;

	DES_set_key(&expanded_key1, &SchKey1);

    DES_ecb_encrypt(&input_data, &cipher, &SchKey1, DES_ENCRYPT);

    for (int i = 0; i < 8; i++) {
    	Hash[i] = cipher[i];
    }

}

void setup_des_key(unsigned char key_56[], DES_key_schedule &ks)
{
	DES_cblock key;

	key[0] = key_56[0];
	key[1] = (key_56[0] << 7) | (key_56[1] >> 1);
	key[2] = (key_56[1] << 6) | (key_56[2] >> 2);
	key[3] = (key_56[2] << 5) | (key_56[3] >> 3);
	key[4] = (key_56[3] << 4) | (key_56[4] >> 4);
	key[5] = (key_56[4] << 3) | (key_56[5] >> 5);
	key[6] = (key_56[5] << 2) | (key_56[6] >> 6);
	key[7] = (key_56[6] << 1);

	//des_set_odd_parity(&key);
	DES_set_key(&key, &ks);
}

void HashNetNTLMv1(
	unsigned char	*pData,
	unsigned int	uLen,		// uLen == 7
	unsigned char	Hash[8])
{

    int i;
	for (i = uLen; i < 7; i++)
		pData[i] = 0;

	static unsigned char magic[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
	
	DES_key_schedule ks;

	setup_des_key(pData, ks);
	DES_ecb_encrypt((DES_cblock*)magic, (DES_cblock*)Hash, &ks, DES_ENCRYPT);

}