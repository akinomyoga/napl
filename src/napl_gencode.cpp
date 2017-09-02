#include "napl.hpp"

std::vector<vm_opcode>& GenerateCode::get_code()noexcept
{
    return this->opcode;
}

int GenerateCode::get_count() const noexcept
{
    return code_count;
}

void GenerateCode::gencode(opcode_type type)
{
    vm_opcode op;

    op.type=type;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,int i_value)
{
    vm_opcode op;

    op.type=type;
    op.i_value=i_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,double f_value)
{
    vm_opcode op;

    op.type=type;
    op.f_value=f_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,char* s_value)
{
    vm_opcode op;

    op.type=type;
    op.s_value=s_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,std::string s_value)
{
    vm_opcode op;

    op.type=type;
    op.s_value=s_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,bool b_value)
{
    vm_opcode op;

    op.type=type;
    op.b_value=b_value;

    opcode.push_back(op);
}

std::string GenerateCode::get_dump_tree_str(node_t *node)
{
    switch(node->type)
    {
        case ast_type::nop: return "nop";
        case ast_type::int_value: return "int_value:"+std::to_string(node->i_value);
        case ast_type::float_value: return "float_value:"+std::to_string(node->f_value);
        case ast_type::string_value: return "string_value:"+node->s_value;
        case ast_type::bool_value: return "bool_value:"+std::to_string(node->b_value);
        case ast_type::add: return "add";
        case ast_type::sub: return "sub";
        case ast_type::mul: return "mul";
        case ast_type::div: return "div";
        case ast_type::mod: return "mod";
        case ast_type::output: return "output";
        case ast_type::eq: return "eq";
        case ast_type::noteq: return "noteq";
        case ast_type::great: return "great";
        case ast_type::greateq: return "greateq";
        case ast_type::less: return "less";
        case ast_type::lesseq: return "lesseq";
        case ast_type::write_memory: return "write_memory";
        case ast_type::ref_memory: return "ref_memory";
    }
}

void GenerateCode::dump_tree(std::string msg,int deep)
{
    for(int i=0;i<deep;i++)
        std::cout<<"\t"<<std::flush;

    std::cout<<"{"<<msg<<"}"<<std::endl;
}

void GenerateCode::gencode_tree(node_t *ast_node)
{
    #ifdef DUMP_TREE
    static int tree_deep=0;
    #endif

    if(ast_node==nullptr)
    {
        return;
    }

    #ifdef DUMP_TREE
    dump_tree(get_dump_tree_str(ast_node),tree_deep);
    #endif

    #ifdef DUMP_TREE
    tree_deep++;
    #endif

    gencode_tree(ast_node->left);
    gencode_tree(ast_node->right);
    
    #ifdef DUMP_TREE
    tree_deep--;
    #endif

    switch(ast_node->type)
    {
        case ast_type::nop: break;
        case ast_type::int_value: gencode(opcode_type::PUSH_I,ast_node->i_value); break;
        case ast_type::float_value: gencode(opcode_type::PUSH_F,ast_node->f_value); break;
        case ast_type::string_value: gencode(opcode_type::PUSH_S,ast_node->s_value); break;
        case ast_type::bool_value: gencode(opcode_type::PUSH_B,ast_node->b_value); break;
        case ast_type::add: gencode(opcode_type::ADD); break;
        case ast_type::sub: gencode(opcode_type::SUB); break;
        case ast_type::mul: gencode(opcode_type::MUL); break;
        case ast_type::div: gencode(opcode_type::DIV); break;
        case ast_type::mod: gencode(opcode_type::MOD); break;
        case ast_type::output: gencode(opcode_type::OUTPUT); break;
        case ast_type::eq: gencode(opcode_type::EQ); break;
        case ast_type::noteq: gencode(opcode_type::NOTEQ); break;
        case ast_type::great: gencode(opcode_type::GREAT); break;
        case ast_type::greateq: gencode(opcode_type::GREATEQ); break;
        case ast_type::less: gencode(opcode_type::LESS); break;
        case ast_type::lesseq: gencode(opcode_type::LESSEQ); break;
        case ast_type::write_memory: gencode(opcode_type::WRITE_MEM); break;
        case ast_type::ref_memory: gencode(opcode_type::REF_MEM); break;
    }
}