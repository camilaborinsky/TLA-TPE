typedef enum node_type{
    ROOT,
    DECLARATION_N,
    CONSTANT_N,
    CTL_N,
    LOOP_N,
    ARITHMETIC_N,
    FUNCALL_N,
    FUNDECL_N,
}node_type;

typedef struct ast_node_t{
    node_type type;
    ast_node_t * left;
    ast_node_t  * right;

}ast_node_t;