#include <iostream>
#include "./includes/pen-utility.hpp"
using namespace std;
constexpr int size = 768 << 20;
char p[size];
TSeq_arg seq_main;
int main(int argc, char *argv[])
{
//This assembly code expands the system stack space upto 768MB. x86-64 only.
    __asm__("MOV %0, %%RSP\n" :: "r"(p + size));
    string op;
    TSeq_arg * seq_user_args;
    seq_user_args = new TSeq_arg;
    while (true)
    {
        getline(cin, op);
        if (op == "exit")
            break;
        Scanner.append(op);
    }
    for (size_t i = 0; i < Scanner.lexemes.size(); ++i)
    {
        cout << Scanner.lexemes[i];
    }
    cout << endl;
    cout << "########################Token list end#############################" << endl;
    int pos = 0;
    Parser.rebind(Scanner.lexemes);
    int ret_v = (*Parser.execute(pos).int_val);
    delete seq_user_args;
    return ret_v;
}
