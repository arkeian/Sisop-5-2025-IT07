#include "shell.h"
#include "kernel.h"

#define SEGMENT     0xB000
#define ADDRESS     0x8000
#define INT_HEX     0x16
#define TELETYPE    0X0E
#define KEYBOARD    0X00
#define MASK        0x00FF
#define VALID_ASCII 0X20
#define MAX_COLUMNS 80
#define MAX_ROWS    25
#define BUFFER      1024

static unsigned int _xPos = 0, _yPos = 0;
static unsigned int _xStart = 0, _yStart = 0;
static unsigned char _color = 0x05;
char input[BUFFER];

enum KEYCODE {
  KEY_RETURN    = '\r',
  KEY_BACKSPACE = '\b'
};

void main() {
  clearScreen();
  shell();
}

void putc(unsigned char c) {
  unsigned char *ptr;
  unsigned int offset;

  if (c == 0) {
    return;
  }

  if (c == '\n') {
    _xPos = _xStart;
    _yPos++;
    return;
  }

  if (_xPos > MAX_COLUMNS - 1) {
    _xPos = _xStart;
    _yPos++;
    return;
  }

  if (_yPos > MAX_ROWS - 1) {
    _yPos = _yStart;
    return;
  }

  offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;

  putInMemory(SEGMENT, offset, c);
  putInMemory(SEGMENT, offset + 1, _color);

  _xPos++;
}

void repositionXY(unsigned int x, unsigned int y) {
  _xPos = x;
  _yPos = y;
  _xStart = _xPos;
  _yStart = _yPos;
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
  int ax = 0;
  unsigned int offset;

  while (1) {
    ax = interrupt(INT_HEX, KEYBOARD, 0, 0, 0);
    c = (unsigned char)(ax & MASK);

    if (c ==  KEY_RETURN) {
      buf[bufPos] = '\0';
      putc('\n');
      break;
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

