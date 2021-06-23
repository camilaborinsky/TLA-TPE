#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "figures.h"



#define JMP_RATE 500
#define REFRESH_RATE 20
#define GRAVITY 300                           //  px/s*s
#define JMP -0.5f * GRAVITY *JMP_RATE / 1000  +6  //px/s

int WIDTH;
int HEIGHT;


join_figure *player;
double player_y = 0;
double speed = 0;

join_figure *setup_player() {
    rectangle hat = {
        .x = -3,
        .y = 0,
        .width = 7,
        .height = 1,
        .draw = draw_rect};
    circle head = {
        .x = 0,
        .y = 2,
        .radius = 2,
        .draw = draw_circ};

    join_figure *fig = malloc(sizeof(join_figure));

    fig->f1 = malloc(sizeof(figure));
    fig->f2 = malloc(sizeof(figure));

    memcpy(fig->f1, &hat, sizeof(hat));
    memcpy(fig->f2, &head, sizeof(head));

    fig->x = WIDTH / 2;
    fig->y = HEIGHT / 2;
    fig->draw = draw_join_figure;

    return fig;
}

typedef struct interval_callback {
    unsigned long long last_call;
    unsigned int ms;
    void (*callback)(void);
} interval_callback;

interval_callback callbacks[128];
int callback_index = 0;

void set_interval(unsigned int ms, void (*callback)(void)) {
    callbacks[callback_index].callback = callback;
    callbacks[callback_index].ms = ms;
    callbacks[callback_index].last_call = 0;
    callback_index++;
}

unsigned long long millis() {
    struct timeval current;
    gettimeofday(&current, 0);
   return current.tv_sec * 1000 + current.tv_usec / 1000;
}

void loop() {
    while (1) {

        unsigned long long current_millis = millis();
        for (int i = 0; i < callback_index; i++) {
            if (callbacks[i].ms < current_millis - callbacks[i].last_call) {
                callbacks[i].last_call = current_millis;
                callbacks[i].callback();
            }
        }
    }
}

void update() {
    clear();
    player_y += speed * REFRESH_RATE / 1000;
    move_figure((figure *)player, WIDTH / 2, player_y);
    speed = speed + GRAVITY * REFRESH_RATE * 1.0f / 1000;
    player->draw(player);
    char buffer[128];
    sprintf(buffer,
            "refresh rate: %d\n"
            "jmp rate: %d\n"
            "gravity: %d\n"
            "jmp: %f\n"
            "speed: %f\n"
            "y: %f\n",
            REFRESH_RATE, JMP_RATE, GRAVITY, JMP, speed, player_y);

    mvaddstr(0, 0, buffer);
    refresh();
}

void jump() {
    speed = JMP;
}

int main() {
    initscr();
    noecho();
    start_color();
    curs_set(0);
    getmaxyx(stdscr, HEIGHT, WIDTH);
    player_y = HEIGHT / 2;
    WIDTH = WIDTH / 2;
    refresh();
    player = setup_player();

    set_interval(REFRESH_RATE, update);
    set_interval(JMP_RATE, jump);
    loop();
}