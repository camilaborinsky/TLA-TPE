#ifndef FIGURES_H
#define FIGURES_H

#include <ncurses.h>

typedef struct rectangle rectangle;
typedef struct circle circle;
typedef struct line line;
typedef struct dot dot;
typedef struct join_figure join_figure;
typedef struct figure figure;


void init();

void draw(figure *);
void move_figure(figure *, int x, int y);

rectangle * rect_init(int x, int y, int w, int h);
circle * circ_init(int x, int y, int r);
line * line_init(int x, int y, int z, int w);
dot * dot_init(int x, int y);
join_figure *join(figure *f1, figure *f2);

void destroy(figure * fig);

extern int width;
extern int height;

void easter_egg();

void cursor(int,int);
void print(char * str);
void printN(int n);
void printD(double d);
void printC(int c);
char * concat(char * s1, char * s2);
char * append(char * s, int c);

#endif