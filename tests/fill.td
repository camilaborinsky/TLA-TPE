
function get_input:int(){
    let num:int = -1;
    while(num == -1){
        num = in();
    }
    return num;
}



while(true){
    let num:int = (get_input() - 47)*width/10;
    clear();
    let r:rectangle = rect_init(0,0,num,height);
    draw(r);
}