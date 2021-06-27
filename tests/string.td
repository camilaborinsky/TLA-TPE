
function print_concat:void(str1:text,str2:text){
    print --> concat(str1,str2);
    return;
}

print_concat("hola","como andas");
printC --> 10;

function get_in:text(input:text){
    let c:int = -1;
    while(c == -1){
        c = in();
    }
    return append(input, c);
}

function append_test:void(){
    let input:text = "";
    
    
    while(true){
        input = get_in(input);
        print --> append(input,10);
    }
    return;

}


append_test();
