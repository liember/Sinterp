#pragma once
#include <stddef.h>

unsigned int sspn(const char *string, const char *reject);
int scmp(const char *p1, const char *p2);
char *stok(char *s, const char *ct);
unsigned int slen(const char *s);
char *scpy(char *destination, const char *src);
char isdigi(char c);
void StrDelim(char *str);
char *MoveToNextDelim(char *str);
