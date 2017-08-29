#include "napl.hpp"

node_t *make_node(ast_type type,node_t *l,node_t *r)
{
    node_t *new_node=new node_t;

    new_node->type=type;
    new_node->left=l;
    new_node->right=r;

    return new_node;
}

node_t *make_atom(ast_type type,int i)
{
    node_t *new_atom=new node_t;

    new_atom->type=type;
    new_atom->i_value=i;
    new_atom->left=nullptr;
    new_atom->right=nullptr;

    return new_atom;
}

node_t *make_atom(ast_type type,double f)
{
    node_t *new_atom=new node_t;

    new_atom->type=type;
    new_atom->f_value=f;
    new_atom->left=nullptr;
    new_atom->right=nullptr;

    return new_atom;
}

node_t *make_atom(ast_type type,std::string s)
{
    node_t *new_atom=new node_t;

    new_atom->type=type;
    new_atom->s_value=s;
    new_atom->left=nullptr;
    new_atom->right=nullptr;

    return new_atom;
}

node_t *make_atom(ast_type type,bool b)
{
    node_t *new_atom=new node_t;

    new_atom->type=type;
    new_atom->b_value=b;
    new_atom->left=nullptr;
    new_atom->right=nullptr;

    return new_atom;
}