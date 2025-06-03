#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

void shell(){
  char buf[128];
  printString("Welcome to EorzeOS!\n");
  while (true) {
    printString("> ");
    readString(buf);
    printString(buf);
    printString("\n");
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0;
    int j = 0;
    int arg_index = 0;

    while (buf[i] == ' ' && buf[i] != '\0') i++;

    j = 0;
    while (buf[i] != '\0' && buf[i] != ' ' && j < 63) {
        cmd[j] = buf[i];
        i++;
        j++;
    }
    cmd[j] = '\0';

    while (buf[i] == ' ' && buf[i] != '\0') i++;

    for (arg_index = 0; arg_index < 2; arg_index++) {
        j = 0;
        if (buf[i] == '\0') {
            arg[arg_index][0] = '\0';
            continue;
        }
        
        while (buf[i] != '\0' && buf[i] != ' ' && j < 63) {
            arg[arg_index][j] = buf[i];
            i++;
            j++;
        }
        arg[arg_index][j] = '\0';
        
        while (buf[i] == ' ' && buf[i] != '\0') i++;
    }
}

// Tambahkan fungsi bila perlu
