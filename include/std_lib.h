#ifndef __STD_TYPE_H__
#define __STD_TYPE_H__

#ifdef NULL
#undef NULL
#endif

#define NULL (void *)0

typedef unsigned char byte;

typedef char bool;
#define true 1
#define false 0

#define CT_UP	0x01
#define CT_LOW	0x02
#define CT_DIG	0x04
#define CT_WHT	0x20
#define CT_HEX	0x40

#define isalnum(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP | CT_LOW | CT_DIG))
#define isalpha(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP | CT_LOW))
#define isdigit(c)	((_ctype + 1)[(unsigned)(c)] & (CT_DIG))
#define isupper(c)	((_ctype + 1)[(unsigned)(c)] & (CT_UP))
#define islower(c)	((_ctype + 1)[(unsigned)(c)] & (CT_LOW))
#define isspace(c)	((_ctype + 1)[(unsigned)(c)] & (CT_WHT))
#define isxdigit(c)	((_ctype + 1)[(unsigned)(c)] & (CT_DIG | CT_HEX))
#define isascii(c)	((unsigned)(c) <= 0x7F)
#define toascii(c)	((unsigned)(c) & 0x7F)
#define tolower(c)	(isupper(c) ? c + 'a' - 'A' : c)
#define toupper(c)	(islower(c) ? c + 'A' - 'a' : c)

#endif // __STD_TYPE_H__
