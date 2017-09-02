#ifndef NAPL_TREE_HPP
#define NAPL_TREE_HPP

enum class ast_type : int
{

    nop,

    int_value,float_value,string_value,bool_value,

    add,sub,mul,div,mod,

    eq,noteq,great,greateq,less,lesseq,

    output,

    write_memory,ref_memory,
};

struct node_t
{

    ast_type type;

    node_t *left;
    node_t *right;

    union
    {
        int i_value;
        double f_value;
        bool b_value;
    };

    std::string s_value;

};

#endif