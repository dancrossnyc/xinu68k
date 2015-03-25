// Swap bytes in 16-bit [half-]words
// for going between the 11 and the interdata

int
swab(short *pf, short *pt, int n)
{

	n /= 2;
	while (--n >= 0) {
		*pt++ = (*pf << 8) + ((*pf >> 8) & 0377);
		pf++;
	}
}
