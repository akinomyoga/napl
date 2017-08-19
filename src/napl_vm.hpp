#ifndef NAPL_VM_HPP
#define NAPL_VM_HPP

enum class stack_type : int
{

    INT,FLOAT,STRING,BOOL,

};

typedef struct
{
    stack_type type;

    union
    {
        int i_value;
        double f_value;
        char* s_value;
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

        void push(int);
        void push(double);
        void push(char *);
        void push(bool);

        void print();

        vm_stack pop();

        inline bool check_stack_type(stack_type,stack_type);

        void error(std::string);

        void debug();

    public:

        void exec_code();

        NaplVM(std::vector<vm_opcode>&);
};

#endif