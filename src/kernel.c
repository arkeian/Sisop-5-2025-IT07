#include "shell.h"
#include "kernel.h"

#define SEGMENT     0xB000
#define ADDRESS     0x8000
#define INT_VID     0x10
#define INT_KBD     0x16
#define TELETYPE    0X0E
#define KEYBOARD    0X00
#define MASK        0x00FF
#define VALID_ASCII 0X20
#define SCROLL      0x06
#define SCROLL_ONE  0x01
#define IGNORE      0x00
#define MAX_COLUMNS 80
#define MAX_ROWS    25
#define TAB_SIZE    4
#define BUFFER      128

static unsigned int _xPos = 0, _yPos = 0;
static unsigned int _xStart = 0, _yStart = 0;
static unsigned char _color = 0x0F;

enum KEYCODE {
  KEY_NEWLINE   = '\n',
  KEY_RETURN    = '\r',
  KEY_TAB       = 0x09,
  KEY_BACKSPACE = 0x08
};

void main() {
  clearScreen();
  shell();
}

void repositionXY(unsigned int x, unsigned int y) {
  _xPos = x;
  _yPos = y;
  _xStart = _xPos;
  _yStart = _yPos;
}  

/*
void scroll() {
  unsigned int from, to;
  unsigned int offset;
  int i, j;
  char buf, attribute;

  for (i = 1; i < MAX_ROWS; i++) {
    for (j = 0; j < MAX_COLUMNS; j++) {
      from = ADDRESS + (i * MAX_COLUMNS + j) * 2;
      to = ADDRESS + ((i - 1) * MAX_COLUMNS + j) * 2;
      buf = *(char *)(SEGMENT * 16 + from);
      attribute = *(char *)(SEGMENT * 16 + from + 1);

      putInMemory(SEGMENT, to, buf);
      putInMemory(SEGMENT, to + 1, attribute);
    }
  }

  for (j = 0; j < MAX_COLUMNS; j++) {
      offset = ADDRESS + ((MAX_ROWS - 1) * MAX_COLUMNS + j) * 2;

      putInMemory(SEGMENT, offset, ' ');
      putInMemory(SEGMENT, offset + 1, _color);
  }

  repositionXY(0, MAX_ROWS - 1);
}
*/

void scroll() {
  unsigned int ax, bx, cx, dx;

  ax = (SCROLL << 8) | SCROLL_ONE;
  bx = (_color << 8) | IGNORE;
  cx = (0 << 8) | 0;
  dx = ((MAX_ROWS - 1) << 8) | (MAX_COLUMNS - 1);

  interrupt(INT_VID, ax, bx, cx, dx);

  repositionXY(0, MAX_ROWS - 1);
}

void putc(unsigned char c) {
  unsigned char *ptr;
  unsigned int offset;

  if (c == 0) {
    return;
  }  
  else if (c == KEY_NEWLINE) {
    _xPos = _xStart;
    _yPos++;
    return;
  }

  if (_xPos >= MAX_COLUMNS) {
    _xPos = _xStart;
    _yPos++;
  }  

  if (_yPos >= MAX_ROWS) {
    scroll();
  }  

  offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;

  putInMemory(SEGMENT, offset, c);
  putInMemory(SEGMENT, offset + 1, _color);

  _xPos++;
}  


void printString(char *str)
{
  if (str == 0) {
    return;
  }  

  while(*str) {
    putc(*str);
    str++;
  }  
}  

void readString(char *buf) {
  unsigned char c;
  int bufPos = 0;
  unsigned int ax;
  unsigned int offset;
  int i;

  while (1) {
    ax = interrupt(INT_KBD, KEYBOARD, 0, 0, 0);
    c = (unsigned char)(ax & MASK);

    if (c == KEY_RETURN) {
      buf[bufPos] = '\0';
      putc(KEY_NEWLINE);
      break;
    }
    else if (c == KEY_TAB) {
      for (i = 0; i < TAB_SIZE; i++) {
        buf[bufPos] = ' ';
        bufPos++;
        putc(' ');
      }
    }  
    else if (c == KEY_BACKSPACE) {
      if (bufPos > 0) {
        bufPos--;

        if (_xPos > _xStart) {
          _xPos--;
        }  
        else if (_yPos > _yStart) {
          _yPos--;
          _xPos = MAX_COLUMNS - 1;
        }  

        offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;
  
        putInMemory(SEGMENT, offset, ' ');
        putInMemory(SEGMENT, offset + 1, _color);
      }  
    }  
    else {
      if (c >= VALID_ASCII && bufPos < BUFFER - 1) {
        buf[bufPos] = c;
        bufPos++;
        putc(c);
      }  
    }  
  }  
}  

void clearScreen() {
  unsigned int offset;
  int i, j;
  
  for (i = 0; i < MAX_ROWS; i++) {
    for (j = 0; j < MAX_COLUMNS; j++) {
      offset = ADDRESS + (i * MAX_COLUMNS + j) * 2;

      putInMemory(SEGMENT, offset, ' ');
      putInMemory(SEGMENT, offset + 1, _color);
    }  
  }  

  repositionXY(0, 0);
}  

