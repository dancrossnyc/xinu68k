#include "u.h"

unsigned short
cksum(unsigned short *p, size_t words)
{
	uint32 sum;

	sum = 0;
	for (int k = 0; k < words; k++)
		sum += *p++;
	while ((sum >> 16) != 0)
		sum = (sum >> 16) + (sum & 0xFFFF);

	return (~sum) & 0xFFFF;
}
