#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "lib/figures.h"
#include "lib/handlers.h"

void vIddDBkEvh() {
    rectangle* f1 = rect_init(0, 0, 10, 10);
    circle* f2 = circ_init(10, 10, 5);
    figure* f3 = join(f1, f2);
    return;
}
int main() {
    init();
    set_interval(60, vIddDBkEvh);
    loop();
    return 0;
}
