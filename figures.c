#include "figures.h"
#include <stdlib.h>
#include <math.h>

#define pix -1

#define setpix(y, x, ch)                 \
    {                                    \
        mvaddch((y), 2 * (x), (ch));     \
        mvaddch((y), 2 * (x) + 1, (ch)); \
    }


int offset_y = 0;
int offset_x = 0;

void draw_rect(rectangle *rect) {
    for (int x = 0; x < rect->width; x++)
        for (int y = 0; y < rect->height; y++)
            setpix(offset_y - y - rect->y, offset_x + x + rect->x, pix);
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