#ifndef FIGURES_H
#define FIGURES_H

#include <ncurses.h>

typedef struct rectangle {
    void (*draw)(struct rectangle *);
    int x, y;
    int width, height;
} rectangle;

typedef struct circle {
    void (*draw)(struct circle *);
    int x, y;
    int radius;
} circle;

typedef struct join_figure {
    void (*draw)(struct join_figure *);
    int x, y;
    struct figure *f1;
    struct figure *f2;
} join_figure;

#define PADDING_SIZE sizeof(join_figure)

typedef struct figure {
    void (*draw)(struct figure *);
    int x, y;
    char data[PADDING_SIZE];
} figure;

void draw_rect(rectangle *);
void draw_circ(circle *);
void draw_join_figure(join_figure *);
void move_figure(figure *, int x, int y);

extern int offset_x;
extern int offset_y;

#endif