#include "std_lib.h"
#include "std_type.h"

int div(int a, int b) {
  //TODO: Implementasi pembagian
  //NOTE: HARUS BISA ANGKA NEGATIF
}

int mod(int a, int b)
{
  //TODO: Implementasi modulus
}

bool strcmp(char *str1, char *str2) {
  int res = 0;
  while (*str2 != '\0') {
    res = *(unsigned char *)str1 - *(unsigned char *)str2);
    if (res != 0) {
      break;
    }
    
    ++str1;
    ++str2;
  }

  if (res < 0 || res > 0) {
    res = 0;
  }
  else if (res == 0) {
    res = 1;
  }

  return res;
}

void strcpy(char *dst, char *src) {
  char *dst_ptr = dst;

  while (*dst != '\0' && *src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  
  return *dst_ptr;
}

size_t strlen(const char *str) {
  size_t len = 0;

  while (*str != '\0') {
    len++;
    str++;
  }

  return len;
}

void clear(byte *buf, unsigned int size)
{
  //TODO: Implementasi pembersihan buffer
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
    if (!isdigit(str[pos])) {
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

  while (num != 0) {
    if (num < 0) {
      num *= -1;
      is_negative = 1;
    }
    tbuf[pos] = (char)('0' + (num % 10));
    pos++;
    num /= 10;
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
