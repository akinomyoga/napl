#include "napl.hpp"
#include "napl_vm.hpp"

int main(int argc,char **argv)
{
    std::vector<vm_opcode> naplvm_code;
    naplvm_code.push_back({opcode_type::PUSH_I,12});

    NaplVM vm(naplvm_code);

    vm.exec_code();

    return 0;
}