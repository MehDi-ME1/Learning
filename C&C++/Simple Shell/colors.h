#ifndef COLORS_H
#define COLORS_H

#include <stdio.h>
#include <string.h>

// ANSI color codes
#define COL_RESET   "\033[0m"
#define COL_BLACK   "\033[30m"
#define COL_RED     "\033[31m"
#define COL_GREEN   "\033[32m"
#define COL_YELLOW  "\033[33m"
#define COL_BLUE    "\033[34m"
#define COL_MAGENTA "\033[35m"
#define COL_CYAN    "\033[36m"
#define COL_WHITE   "\033[37m"
#define COL_BRIGHT_BLACK   "\033[90m"
#define COL_BRIGHT_RED     "\033[91m"
#define COL_BRIGHT_GREEN   "\033[92m"
#define COL_BRIGHT_YELLOW  "\033[93m"
#define COL_BRIGHT_BLUE    "\033[94m"
#define COL_BRIGHT_MAGENTA "\033[95m"
#define COL_BRIGHT_CYAN    "\033[96m"
#define COL_BRIGHT_WHITE   "\033[97m"

#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"
#define BG_BRIGHT_BLACK   "\033[100m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"

// Text styles
#define BOLD       "\033[1m"
#define DIM        "\033[2m"
#define ITALIC     "\033[3m"
#define UNDERLINE  "\033[4m"
#define BLINK      "\033[5m"
#define REVERSE    "\033[7m"
#define HIDDEN     "\033[8m"

// Simple color printing function
static void colprint(const char* text, const char* text_color, const char* background_color) {
    if (text_color == NULL) {
        printf("%s", text);
        return;
    }

    // Text colors
    if (strcmp(text_color, "black") == 0) printf(COL_BLACK);
    else if (strcmp(text_color, "red") == 0) printf(COL_RED);
    else if (strcmp(text_color, "green") == 0) printf(COL_GREEN);
    else if (strcmp(text_color, "yellow") == 0) printf(COL_YELLOW);
    else if (strcmp(text_color, "blue") == 0) printf(COL_BLUE);
    else if (strcmp(text_color, "magenta") == 0) printf(COL_MAGENTA);
    else if (strcmp(text_color, "cyan") == 0) printf(COL_CYAN);
    else if (strcmp(text_color, "white") == 0) printf(COL_WHITE);
    else if (strcmp(text_color, "bright_black") == 0) printf(COL_BRIGHT_BLACK);
    else if (strcmp(text_color, "bright_red") == 0) printf(COL_BRIGHT_RED);
    else if (strcmp(text_color, "bright_green") == 0) printf(COL_BRIGHT_GREEN);
    else if (strcmp(text_color, "bright_yellow") == 0) printf(COL_BRIGHT_YELLOW);
    else if (strcmp(text_color, "bright_blue") == 0) printf(COL_BRIGHT_BLUE);
    else if (strcmp(text_color, "bright_magenta") == 0) printf(COL_BRIGHT_MAGENTA);
    else if (strcmp(text_color, "bright_cyan") == 0) printf(COL_BRIGHT_CYAN);
    else if (strcmp(text_color, "bright_white") == 0) printf(COL_BRIGHT_WHITE);

    // Background colors
    if (background_color != NULL) {
        if (strcmp(background_color, "black") == 0) printf(BG_BLACK);
        else if (strcmp(background_color, "red") == 0) printf(BG_RED);
        else if (strcmp(background_color, "green") == 0) printf(BG_GREEN);
        else if (strcmp(background_color, "yellow") == 0) printf(BG_YELLOW);
        else if (strcmp(background_color, "blue") == 0) printf(BG_BLUE);
        else if (strcmp(background_color, "magenta") == 0) printf(BG_MAGENTA);
        else if (strcmp(background_color, "cyan") == 0) printf(BG_CYAN);
        else if (strcmp(background_color, "white") == 0) printf(BG_WHITE);
        else if (strcmp(background_color, "bright_black") == 0) printf(BG_BRIGHT_BLACK);
        else if (strcmp(background_color, "bright_red") == 0) printf(BG_BRIGHT_RED);
        else if (strcmp(background_color, "bright_green") == 0) printf(BG_BRIGHT_GREEN);
        else if (strcmp(background_color, "bright_yellow") == 0) printf(BG_BRIGHT_YELLOW);
        else if (strcmp(background_color, "bright_blue") == 0) printf(BG_BRIGHT_BLUE);
        else if (strcmp(background_color, "bright_magenta") == 0) printf(BG_BRIGHT_MAGENTA);
        else if (strcmp(background_color, "bright_cyan") == 0) printf(BG_BRIGHT_CYAN);
        else if (strcmp(background_color, "bright_white") == 0) printf(BG_BRIGHT_WHITE);
    }

    printf("%s%s", text, COL_RESET);
}

// Convenience functions
static void colprint_red(const char* text) { colprint(text, "red", NULL); }
static void colprint_green(const char* text) { colprint(text, "green", NULL); }
static void colprint_yellow(const char* text) { colprint(text, "yellow", NULL); }
static void colprint_blue(const char* text) { colprint(text, "blue", NULL); }
static void colprint_magenta(const char* text) { colprint(text, "magenta", NULL); }
static void colprint_cyan(const char* text) { colprint(text, "cyan", NULL); }

// Style functions
static void colprint_bold(const char* text, const char* color) {
    printf(BOLD);
    colprint(text, color, NULL);
}

static void colprint_underline(const char* text, const char* color) {
    printf(UNDERLINE);
    colprint(text, color, NULL);
}

#endif // COLORS_H
