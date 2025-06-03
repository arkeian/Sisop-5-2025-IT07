#include "shell.h"
#include "std_lib.h"
#include "kernel.h"

#define MAX_HISTORY 20
#define BUFFER_SIZE 128

char current_user[64] = "user";
char history[MAX_HISTORY][BUFFER_SIZE];
int history_count = 0;

void shell() {
    char buf[BUFFER_SIZE];
    char original_input[BUFFER_SIZE];
    char cmd[64];
    char args[10][64];
    int arg_count;
    int num1, num2;
    int resint;
    char resstr[12];

    printString("Welcome to EorzeOS!\n");
    
    while (true) {
        clear(buf, BUFFER_SIZE);
        printString(current_user);
        printString("> ");

        readString(buf);
        strcpy(original_input, buf);

        // Simpan ke history (jika tidak kosong)
        if (buf[0] != '\0') {
            if (history_count < MAX_HISTORY) {
                strcpy(history[history_count++], buf);
            } else {
                // Geser seluruh history ke bawah, buang index 0, tambahkan di akhir
                int i;
                for (i = 0; i < MAX_HISTORY-1; i++) {
                    strcpy(history[i], history[i+1]);
                }
                strcpy(history[MAX_HISTORY-1], buf);
            }
        }

        parseCommand(buf, cmd, args, &arg_count);

        if (cmd[0] == '\0') continue;

        // exit / quit
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            printString("Bye, ");
            printString(current_user);
            printString("!\n");
            break;
        }
        // help
        else if (strcmp(cmd, "help") == 0) {
            printString("Available commands:\n");
            printString("  user [name]    : Change current username\n");
            printString("  history        : Show last commands\n");
            printString("  yo             : Print 'gurt'\n");
            printString("  gurt           : Print 'yo'\n");
            printString("  exit/quit      : Exit shell\n");
            printString("  help           : Show this message\n");
            printString("  (else)         : Echo input\n");
        }
        // user
        else if (strcmp(cmd, "user") == 0) {
            if (arg_count >= 1 && args[0][0] != '\0') {
                strcpy(current_user, args[0]);
                printString("Username changed to ");
                printString(current_user);
            } else {
                strcpy(current_user, "user");
                printString("Username changed to user");
            }
            printString("\n");
        }
        // history
        else if (strcmp(cmd, "history") == 0) {
            int i;
            for (i = 0; i < history_count; i++) {
                printString(history[i]);
                printString("\n");
            }
        }
        // yo dan gurt
        else if (strcmp(cmd, "yo") == 0) {
            printString("gurt\n");
        } else if (strcmp(cmd, "gurt") == 0) {
            printString("yo\n");
        }
        else if (strcmp(cmd, "div") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = div(num1, num2);
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "add") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = num1 + num2;
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "mul") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = num1 * num2;
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "sub") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = num1 - num2;
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        // else echo
        else {
            printString(original_input);
            printString("\n");
        }
    }
}

void parseCommand(char *buf, char *cmd, char arg[10][64], int *arg_count) {
    int i = 0, j = 0, k;
    *arg_count = 0;

    // Lewati spasi awal
    while (buf[i] != '\0' && buf[i] == ' ') i++;

    // Baca cmd
    j = 0;
    while (buf[i] != '\0' && buf[i] != ' ' && j < 63) {
        cmd[j++] = buf[i++];
    }
    cmd[j] = '\0';

    // Lewati spasi sebelum arg
    while (buf[i] != '\0' && buf[i] == ' ') i++;

    // Baca argumen sebanyak mungkin (maks 9, sisanya diabaikan)
    for (k = 0; k < 10; k++) {
        int m = 0;
        if (buf[i] == '\0' || *arg_count >= 9) {
            arg[k][0] = '\0';
            continue;
        }
        while (buf[i] != '\0' && buf[i] != ' ' && m < 63) {
            arg[k][m++] = buf[i++];
        }
        arg[k][m] = '\0';
        (*arg_count)++;

        while (buf[i] != '\0' && buf[i] == ' ') i++;
    }
}