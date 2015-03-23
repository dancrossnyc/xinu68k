static long randx = 1;

int
srand(unsigned x)
{
	randx = x;
}

int
rand(void)
{
	return (((randx = randx * 1103515245 + 12345) >> 16) & 077777);
}
