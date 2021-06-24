#ifndef FIGURES_H
#define FIGURES_H

#include <ncurses.h>

typedef struct rectangle rectangle;
typedef struct circle circle;
typedef struct join_figure join_figure;
typedef struct figure figure;


void init();

void draw(figure *);
void move_figure(figure *, int x, int y);

rectangle * rect_init(int x, int y, int w, int h);
circle * circ_init(int x, int y, int r);
join_figure *join(int x, int y, figure *f1, figure *f2);

void destroy(figure * fig);

extern int screen_width;
extern int screen_height;

#endif