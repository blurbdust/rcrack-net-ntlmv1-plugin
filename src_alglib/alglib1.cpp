
#include "DES.h"

#define MIN_HASH_LEN		8
#define MAX_HASH_LEN		8

struct HashAlgorithmEntry
{
	char			*szName;
	void			*pHashAlgorithm;
	unsigned int	uHashLen;		// MIN_HASH_LEN <= uHashLen <= MAX_HASH_LEN
	unsigned int	uPlaintextLenMin;
	unsigned int	uPlaintextLenMax;
};

struct HashAlgorithmEntry HashAlgorithms[] = {  // this symbol will be exported
	{(char *)"mydes",						(void *)MyDES,							8,		7,	7},
	{(char *)"netntlmv1",					(void *)MyDES,							8,		7,	7},
	{(char *)0,								(void *)0,								0,		0,	0},
};
