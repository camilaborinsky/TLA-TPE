#include "handlers.h"

#include <ncurses.h>
#include <sys/time.h>

#define MAX_CALLBACKS 128

typedef struct interval_callback {
    unsigned long long last_call;
    unsigned int ms;
    void (*callback)(void);
} interval_callback;

typedef struct key_handler {
    int key;
    void (*handler)(void);
} key_handler;

interval_callback callbacks[MAX_CALLBACKS];
int callback_index = 0;

key_handler handlers[MAX_CALLBACKS];
int handler_index = 0;

unsigned long long millis() {
    struct timeval current;
    gettimeofday(&current, 0);
    return current.tv_sec * 1000 + current.tv_usec / 1000;
}

void set_interval(unsigned long long ms, void (*callback)(void)) {
    callbacks[callback_index].callback = callback;
    callbacks[callback_index].ms = ms;
    callbacks[callback_index].last_call = 0;
    callback_index++;
}
void on_key(int key, void (*handler)(void)) {
    handlers[handler_index].handler = handler;
    handlers[handler_index].key = key;
    handler_index++;
}

void loop() {
    while (1) {
        int ch = getch();
        unsigned long long current_millis = millis();
        for (int i = 0; i < callback_index; i++) {
            if (callbacks[i].ms < current_millis - callbacks[i].last_call) {
                callbacks[i].last_call = current_millis;
                callbacks[i].callback();
            }
        }

        for (int i = 0; i < handler_index; i++) {
            {
                if (handlers[i].key == ch) handlers[i].handler();
            }
        }
    }
}