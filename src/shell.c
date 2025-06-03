// shell_with_history_cd.c

#include "shell.h"
#include "kernel.h"
#include "std_lib.h"
#include <string.h>

#define MAX_HISTORY 20

char current_user[64] = "user";
char history[MAX_HISTORY][128];
int history_count = 0;

static void parseCommand(char *buf, char *cmd, char arg[10][64], int *arg_count);
static int string_compare(const char *s1, const char *s2);
static void string_copy(char *dest, const char *src);

void shell() {
    char buf[128];
    char original_input[128];
    char cmd[64];
    char args[10][64];
    int arg_count;

    printString("Welcome to EorzeOS!\n");

    while (true) {
        printString(current_user);
        printString("> ");

        readString(buf);
        string_copy(original_input, buf);

        // Simpan ke history (jika tidak kosong)
        if (buf[0] != '\0') {
            if (history_count < MAX_HISTORY) {
                string_copy(history[history_count++], buf);
            } else {
                // Geser seluruh history ke bawah, buang index 0, tambahkan di akhir
                int i;
                for (i = 0; i < MAX_HISTORY-1; i++) {
                    string_copy(history[i], history[i+1]);
                }
                string_copy(history[MAX_HISTORY-1], buf);
            }
        }

        parseCommand(buf, cmd, args, &arg_count);

        if (cmd[0] == '\0') continue;

        // exit / quit
        if (string_compare(cmd, "exit") == 0 || string_compare(cmd, "quit") == 0) {
            printString("Bye, ");
            printString(current_user);
            printString("!\n");
            break;
        }
        // help
        else if (string_compare(cmd, "help") == 0) {
            printString("Available commands:\n");
            printString("  user [name]    : Change current username\n");
            printString("  cd [dir]       : Change directory\n");
            printString("  history        : Show last commands\n");
            printString("  yo             : Print 'gurt'\n");
            printString("  gurt           : Print 'yo'\n");
            printString("  exit/quit      : Exit shell\n");
            printString("  help           : Show this message\n");
            printString("  (else)         : Echo input\n");
        }
        // user
        else if (string_compare(cmd, "user") == 0) {
            if (arg_count >= 1 && args[0][0] != '\0') {
                string_copy(current_user, args[0]);
                printString("Username changed to ");
                printString(current_user);
            } else {
                string_copy(current_user, "user");
                printString("Username changed to user");
            }
            printString("\n");
        }
        // cd
        else if (string_compare(cmd, "cd") == 0) {
            if (arg_count >= 1 && args[0][0] != '\0') {
                int res = changeDirectory(args[0]); // asumsikan syscall
                if (res < 0) {
                    printString("cd: Failed to change directory\n");
                }
            } else {
                // tanpa argumen, balik ke home (misal root "/")
                changeDirectory("/");
            }
        }
        // history
        else if (string_compare(cmd, "history") == 0) {
            int i;
            for (i = 0; i < history_count; i++) {
                printString(history[i]);
                printString("\n");
            }
        }
        // yo dan gurt
        else if (string_compare(cmd, "yo") == 0) {
            printString("gurt\n");
        } else if (string_compare(cmd, "gurt") == 0) {
            printString("yo\n");
        }
        // else echo
        else {
            printString(original_input);
            printString("\n");
        }
    }
}

static void parseCommand(char *buf, char *cmd, char arg[10][64], int *arg_count) {
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

// Jika ingin pakai custom string compare/copy, gunakan di bawah ini:
static int string_compare(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return (int)(s1[i] - s2[i]);
        i++;
    }
    return (int)(s1[i] - s2[i]);
}

static void string_copy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i++];
    }
    dest[i] = '\0';
}
