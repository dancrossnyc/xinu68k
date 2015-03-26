typedef char *va_list;
#define va_start(list, start) \
		(list) = (char *) \
		    ((sizeof(start) < sizeof(int)) \
			? ((const int *)&(start) + 1) \
			: (const int *)(&(start) + 1))
#define va_arg(list, typ) \
		(sizeof(typ) < sizeof(int) \
		    ? ((list) += sizeof(int), (typ)((const int *)(list))[-1]) \
		    : ((list) += sizeof(typ), (typ)((const typ *)(list))[-1]))
#define va_end(list) ((list) += 0)
