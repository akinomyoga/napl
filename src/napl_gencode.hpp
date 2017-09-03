#ifndef NAPL_GENCODE_HPP
#define NAPL_GENCODE_HPP

class GenerateCode
{

    private:

        std::vector<vm_opcode> opcode;

        std::string get_dump_tree_str(node_t *);
        
        void dump_tree(std::string,int);

    public:

        std::vector<vm_opcode>& get_code()noexcept;

        int get_count()const noexcept;

        void gencode_tree(node_t *);

        void backpatch(int,int);

        void gencode(opcode_type);
        void gencode(opcode_type,int);
        void gencode(opcode_type,double);
        void gencode(opcode_type,char *);
        void gencode(opcode_type,std::string);
        void gencode(opcode_type,bool);

};

#endif