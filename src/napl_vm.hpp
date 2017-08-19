#ifndef NAPL_VM_HPP
#define NAPL_VM_HPP

enum class stack_type : int
{

    INT,FLOAT,CHAR,BOOL,

};

typedef struct
{
    stack_type type;

    union
    {
        int i_value;
        double f_value;
        char c_value;
        bool b_value;
    };

}vm_stack;

class NaplVM
{
    private:

        std::vector<vm_opcode> opcode;
        std::stack<vm_stack> stack;

        int code_counter;

        void add();
        void sub();
        void mul();
        void div();
        void mod();

        template<typename T>
        void push(T);

        void debug();

    public:

        void exec_code();

        NaplVM(std::vector<vm_opcode>&);
};

#endif