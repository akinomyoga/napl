#ifndef NAPL_GENCODE_HPP
#define NAPL_GENCODE_HPP

class GenerateCode
{

    private:

        std::vector<vm_opcode> opcode;

        int code_count;

        std::string get_dump_tree_str(ast_type);
        void dump_tree(std::string,int);

    public:

        std::vector<vm_opcode>& get_code();

        int get_count();

        void gencode_tree(node_t *);

        void gencode(opcode_type);
        void gencode(opcode_type,int);
        void gencode(opcode_type,double);
        void gencode(opcode_type,char *);
        void gencode(opcode_type,std::string);
        void gencode(opcode_type,bool);

};

#endif