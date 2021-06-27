#include <ncurses.h>
#include <stdio.h>

#include "lib/handlers.h"
#include "lib/figures.h"



#define JMP_RATE 500
#define REFRESH_RATE 20
#define GRAVITY 300                           //  px/s*s
#define JMP -0.5f * GRAVITY *JMP_RATE / 1000  +6  //px/s



join_figure *player;
double player_y = 0;
double speed = 0;

join_figure *setup_player() {
    rectangle * hat = rect_init(-3,0,7,1);
    circle * head = circ_init(0,2,2);
    join_figure * fig = join(screen_width/2, screen_height/2, (figure *)hat, (figure *)head);
    return fig;
}



void jump() {
    speed = JMP;
}



void update() {
    clear();
    player_y += speed * REFRESH_RATE / 1000;
    move_figure((figure *)player, screen_width / 2, player_y);
    speed = speed + GRAVITY * REFRESH_RATE * 1.0f / 1000;
    draw((figure *)player);
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

int main() {
    init();
    player = setup_player();
    player_y = screen_height / 2;
    set_interval(REFRESH_RATE, update);
    on_key(' ', jump);
    loop();
}