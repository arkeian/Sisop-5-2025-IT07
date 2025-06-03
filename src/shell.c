#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

void shell(){
   char buf[128];
    char original_input[128];
    char cmd[64];
    char args[2][64];

    printString("Welcome to EorzeOS!\n");

    while (true) {
        printString(current_user);
        printString("> ");
        
        readString(buf);
        
        string_copy(original_input, buf); 
        
        parseCommand(buf, cmd, args);
        
        if (cmd[0] == '\0') {
            continue;
        } else if (string_compare(cmd, "user") == 0) {
            if (args[0][0] != '\0') {
                string_copy(current_user, args[0]);
                printString("Username changed to ");
                printString(current_user);
            } else {
                string_copy(current_user, "user");
                printString("Username changed to user");
            }
            printString("\n");
        } else if (string_compare(cmd, "yo") == 0) {
            printString("gurt\n");
        } else if (string_compare(cmd, "gurt") == 0) {
            printString("yo\n");
        } else {
            printString(original_input);
            printString("\n");
        }
    }
}

static int string_compare(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

static void string_copy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
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
