I solemnly swear that I am up to no good

let player:figure;
let speed:int;
speed = 0;

let player_y:int;
player_y = 10;

function setup_player:figure(){
    
    let hat:rectangle = rect_init(width/2 - 5, height/2, 3, 1);
    
    
    let head:circle = circ_init(width/2, height/2, 2);
    
    return hat join head;
}




     
player = setup_player();

set_interval(50,{
    clear();
    player_y = player_y + speed;
    move_figure(player, 0, player_y);
    draw(player);
    speed = speed + 1;
    cursor --> 0,0;
    print --> "speed ";
    printN --> speed;
    print --> "\n";
    return;

});
on_key(32,{

    speed = -3;
    return;

});

mischief managed
