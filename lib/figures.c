#include "figures.h"

#include <math.h>
#include <stdlib.h>

#define pix -1

#define setpix(y, x, ch)                 \
    {                                    \
        mvaddch((y), 2 * (x), (ch));     \
        mvaddch((y), 2 * (x) + 1, (ch)); \
    }

struct rectangle {
    void (*draw)(struct rectangle *);
    int x, y;
    int width, height;
};

struct circle {
    void (*draw)(struct circle *);
    int x, y;
    int radius;
};

struct line {
    void (*draw)(struct line *);
    int x, y, z, w;
};
struct dot {
    void (*draw)(struct dot *);
    int x, y;
};

struct join_figure {
    void (*draw)(struct join_figure *);
    int x, y;
    struct figure *f1;
    struct figure *f2;
};

union PADDING {
    rectangle rect;
    circle circ;
    join_figure join;
} PADDING;

#define PADDING_SIZE sizeof(PADDING)

struct figure {
    void (*draw)(struct figure *);
    int x, y;
    char data[PADDING_SIZE];
};

int offset_y = 0;
int offset_x = 0;
int screen_width;
int screen_height;

void init() {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    start_color();
    curs_set(0);
    getmaxyx(stdscr, screen_height, screen_width);
    screen_width = screen_width / 2;
    refresh();
}

void draw_rect(rectangle *rect) {
    for (int x = 0; x < rect->width; x++)
        for (int y = 0; y < rect->height; y++)
            setpix(offset_y + y + rect->y, offset_x + x + rect->x, pix);
}

void draw_circ(circle *circ) {
    for (int x = circ->x - circ->radius; x <= circ->x + circ->radius; x++) {
        double radsqr = pow(circ->radius, 2);
        double xsqr = pow(abs(circ->x - x), 2);
        int y = sqrt(abs(radsqr - xsqr));
        setpix(offset_y + y + circ->y, offset_x + x, pix);
        setpix(offset_y - y + circ->y, offset_x + x, pix);
    }
}

void draw_line(line *l) {
    int dx = l->z - l->x;
    int dy = l->w - l->y;

    double tangent = dy == 0 ? 0 : dx * 1.0f / dy;
    
    if (dx < dy) {
        for (int y = 0; y <= dy; y++) {
            int x = y*tangent;
            setpix(offset_y + y + l->y, offset_x + x + l->x, pix);
        }
        return;
    }

    for (int x = 0; x <= dx; x++) {
        int y = x/tangent;
        setpix(offset_y + y + l->y, offset_x + x + l->x, pix);
    }
}

void draw_dot(dot *d) {
    setpix(offset_y + d->y, offset_x + d->x, pix);
}

void draw_join_figure(join_figure *fig) {
    int x_backup = offset_x;
    int y_backup = offset_y;
    offset_x = fig->x;
    offset_y = fig->y;
    if (fig->f1 != NULL) fig->f1->draw(fig->f1);
    if (fig->f2 != NULL) fig->f2->draw(fig->f2);
    offset_x = x_backup;
    offset_y = y_backup;
}

void move_figure(figure *figure, int x, int y) {
    figure->x = x;
    figure->y = y;
}

rectangle *rect_init(int x, int y, int w, int h) {
    rectangle *rect = malloc(sizeof(rectangle));
    rect->draw = draw_rect;
    rect->x = x;
    rect->y = y;
    rect->width = w;
    rect->height = h;
    return rect;
}
circle *circ_init(int x, int y, int r) {
    circle *circ = malloc(sizeof(circle));
    circ->draw = draw_circ;
    circ->x = x;
    circ->y = y;
    circ->radius = r;
    return circ;
}

line *line_init(int x, int y, int z, int w) {
    line *l = malloc(sizeof(line));
    l->draw = draw_line;
    l->x = x;
    l->y = y;
    l->z = z;
    l->w = w;
    return l;
}

dot *dot_init(int x, int y) {
    dot *d = malloc(sizeof(line));
    d->draw = draw_dot;
    d->x = x;
    d->y = y;
    return d;
}

join_figure *join(int x, int y, figure *f1, figure *f2) {
    join_figure *fig = malloc(sizeof(join_figure));

    fig->f1 = f1;
    fig->f2 = f2;

    fig->x = x;
    fig->y = y;
    fig->draw = draw_join_figure;
    return fig;
}

void draw(figure *fig) {
    fig->draw(fig);
    refresh();
}

void destroy(figure *fig) {
    if (fig == NULL) return;
    if (fig->draw == (void (*)(figure *))draw_join_figure) {
        join_figure *join_fig = (join_figure *)fig;
        if (join_fig->f1 != NULL) free(join_fig->f1);
        if (join_fig->f2 != NULL) free(join_fig->f2);
    } else
        free(fig);
}
