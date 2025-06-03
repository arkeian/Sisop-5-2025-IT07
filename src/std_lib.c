#include "std_lib.h"
#include "std_type.h"

#define INT_MAX 32767

int div(int a, int b) {
  int quotient = 0;
  int negative = false;
  int tmpb, multiple;

  if (b == 0) {
    return INT_MAX;
  }

  if (a < 0) {
    a *= -1;
    negative = !negative;
  }
  
  if (b < 0) {
    b *= -1;
    negative = !negative;
  }

  while (a >= b) {
    tmpb = b;
    multiple = 1;

    while ((tmpb << 1) > 0 && (tmpb << 1) <= a) {
      tmpb <<= 1;
      multiple <<= 1;
    }

    a -= tmpb;
    quotient += multiple;
  }

  if (negative) {
    return -quotient;
  }

  return quotient;
}

int mod(int a, int b) {
  int negative = false;
  int tmpb;

  if (b == 0) {
    return 0;
  }

  if (a < 0) {
    a *= -1;
    negative = true;
  }

  if (b < 0) {
    b *= -1;
  }

  while (a >= b) {
    tmpb = b;

    while ((tmpb << 1) > 0 && (tmpb << 1) <= a) {
      tmpb <<= 1;
    }

    a -= tmpb;
  }

  if (negative) {
    return -a;
  }

  return a;
}

int strcmp(char* str1, char* str2) {
	int res = 0;
	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2) {
		++str1, ++str2;
  }

	if (res < 0) {
		res = -1;
  }
	if (res > 0) {
		res = 1;
  }

	return res;
}

char *strcpy(char *dst, char *src) {
  char *dstPtr = dst;

  while (*src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  
  *dst = '\0';

  return dstPtr;
}

void clear(byte *buf, unsigned int size) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num) {
  int tbuf[12];
  int pos = 0;
  int opos = 0;
  int is_negative = 0;
  int base = 1;
  *num = 0;

  if (str[0] == '0' && str[1] == '\0') {
    return;
  }

  if(str[0] == '-') {
    is_negative = 1;
    pos++;
  }
  
  while (str[pos] != '\0') {
    if (!(str[pos] >= '0' && str[pos] <= '9')) {
      break;
    }
    tbuf[pos] = (int)(str[pos] - '0');
    pos++;
  }

  for (opos = pos - 1; opos >= 0; opos--, base *= 10) {
    *num += tbuf[opos] * base;
  }

  if (is_negative) {
    *num *= -1; 
  }
}

void itoa(int num, char *str) {
  char tbuf[12];
  int pos = 0;
  int opos = 0;
  int is_negative = 0;

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  if (num < 0) {
    num *= -1;
    is_negative = 1;
  }

  while (num != 0) {
    tbuf[pos] = (char)('0' + mod(num, 10));
    pos++;
    num = div(num, 10);
  }

  if (is_negative) {
    tbuf[pos] = '-';
    pos++;
  }

  for (opos = 0; opos < pos; pos--, opos++) {
    str[opos] = tbuf[pos - 1];
  }
  str[opos] = '\0';
}
