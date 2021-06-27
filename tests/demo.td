
let player:join_figure;
let speed:double = 0;

function setup_player:figure(){
    
    let hat:rectangle = rect(width/2 - 5, height/2, 10, 10);
    
    
    let head:circle = circ(width/2, height/2, 8);
    
    return hat + head;
}



function main:void(){
     
    player = setup_player();
    
    set_interval(60, () -> {

        player.move(0,player.y + speed);
        player.draw();
        speed = speed - 0.1;

    });
    set_interval(1000, () -> {

        speed = 5;

    });

}