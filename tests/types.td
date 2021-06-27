let d:dot;
let r:rectangle;
let l:line;
let c:circle;
let f:figure;
let t:text;
let n:int;
let dec:double;


d = dot_init(width/2,height/2);
r = rect_init(10,10,3,6);
c = circ_init(width/2,height/2,8);
l = line_init(0,0,width,height/3);

//para comentar se usa //
f= d join r;
f = f join c;
f = f join l;
n=5;
dec = 1.3;
t="imprimiendo";



let direction:int;
direction = 0;
let scale:int;
scale = 10;

set_interval(500,{
    clear();
    let set:bool = false;
    if(direction == 0){
        move_figure(f,scale,0);
        direction = 1;
        set = not set;
    }
    if(not set and direction == 1){
        move_figure(f,scale,scale);
        direction=2;
        set = true;
    }
    if(not set and direction == 2){
        move_figure(f,0,scale);
        direction=3;
        set = 1;
    }
    if(not set and direction == 3){
        move_figure(f,0,0);
        direction=0;
    }
    draw(f);
    cursor --> 0,0;
    printN(5);
    printC(10);
    printD(dec);
    printC(10);
    print --> t;
    return;
});
