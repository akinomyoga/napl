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
        bool b_value;
    };

    std::string s_value;

}vm_stack;

class NaplVM
{
    private:

        std::vector<vm_opcode> opcode;

        std::stack<vm_stack> stack;

        std::map<opcode_type,void (NaplVM::*)()> function_map;

        int code_counter;

        void add();
        void sub();
        void mul();
        void div();
        void mod();

        inline void push(int);
        inline void push(double);
        inline void push(std::string);
        inline void push(bool);

        void print();

        void init_function_map();

        vm_stack pop();

        inline bool check_stack_type(stack_type,stack_type);

        inline void jump();
        inline void jump_not();

        inline void eq();
        inline void noteq();
        inline void great();
        inline void greateq();
        inline void less();
        inline void lesseq();

        inline void exit_vm();

        void error(std::string);

        void debug();

    public:

        void exec_code();

        NaplVM(std::vector<vm_opcode>&);
};

#endif