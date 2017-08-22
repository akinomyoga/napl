#ifndef NAPL_GENCODE_HPP
#define NAPL_GENCODE_HPP

class GenerateCode
{

    private:

        std::vector<vm_opcode> opcode;

        int code_count;

    public:

        std::vector<vm_opcode>& get_code();

        int get_count();

        void gencode(opcode_type);
        void gencode(opcode_type,int);
        void gencode(opcode_type,double);
        void gencode(opcode_type,char *);
        void gencode(opcode_type,std::string);
        void gencode(opcode_type,bool);

};

#endif