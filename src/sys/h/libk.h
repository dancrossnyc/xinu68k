size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t len);
void *memmove(void *dst, const void *src, size_t len);
int memcmp(const void *a, const void *b, size_t len);

// Unsafe functions to remove.
void sprintf(char *dst, const char *fmt, ...);
char *strcpy(char *dst, const char *str);
char *strncpy(char *dst, const char *str, size_t len);
char *strcat(char *dst, const char *src);
char *strncat(char *dst, const char *src, size_t len);

// Weird stuff.
void printf(const char *fmt, ...);
void fprintf(int dev, const char *fmt, ...);
int atoi(const char *s);
