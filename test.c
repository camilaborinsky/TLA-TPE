#include<stdlib.h>
#include<stdio.h>
#include<strings.h>
#include"lib/figures.h"
#include"lib/handlers.h"

rectangle * myRect;
int main(){
myRect = rect_init(1010105);
draw( myRect );
return 0;
}


