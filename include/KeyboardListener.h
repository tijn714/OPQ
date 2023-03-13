#ifndef KEYBOARD_EVENTS_H
#define KEYBOARD_EVENTS_H

#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

void start_keyboard_listener();
void stop_keyboard_listener();
int get_last_key();

#endif // KEYBOARD_EVENTS_H

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#ifdef _WIN32
#include <conio.h>

void start_keyboard_listener() {
    // no-op, _kbhit() is non-blocking
}

void stop_keyboard_listener() {
    // no-op, _kbhit() is non-blocking
}

int get_last_key() {
    return _getch();
}
#else

struct termios orig_termios;

void start_keyboard_listener() {
    struct termios new_termios;
    tcgetattr(0, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &new_termios);
}

void stop_keyboard_listener() {
    tcsetattr(0, TCSANOW, &orig_termios);
}

int get_last_key() {
    int c = getchar();
    if (c != EOF) {
        ungetc(c, stdin);
    }
    return c;
}

#endif

void waitKey() {
    #ifdef _WIN32
       getch();
    #else
       start_keyboard_listener();
       get_last_key();
       stop_keyboard_listener();
    #endif
}