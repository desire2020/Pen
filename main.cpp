#include <iostream>
#include "./includes/pen-utility.hpp"
using namespace std;
TSeq_arg seq_main;
constexpr int size = 1024 << 20;
char p[size];
int main(int argc, char *argv[])
{
//This assembly code expands the system stack space upto 768MB. x86-64 only.
    __asm__("MOVQ %0, %%RSP\n" :: "r"(p + size));
    string op;
    TSeq_arg * seq_user_args;
    seq_user_args = new TSeq_arg;
    if (argc == 1)
    {
        while (true)
        {
            getline(cin, op);
            if (op == "exit")
                break;
            Scanner.append(op);
        }
    } else {
        ifstream fin(argv[1]);
        while (!fin.eof())
        {
            getline(fin, op);
            Scanner.append(op);
        }
    }
    for (size_t i = 0; i < Scanner.lexemes.size(); ++i)
    {
        cout << "Token #" << i << ":\t" << Scanner.lexemes[i] << endl;
    }
    cout << endl;
    cout << "########################Token list end#############################" << endl;
    int pos = 0;
    int ret_v;
    Parser.rebind(Scanner.lexemes);
    while (pos < Scanner.lexemes.size())
        ret_v = (*Parser.execute(pos).int_val);
    delete seq_user_args;
    cout.flush();
    exit(ret_v);
}
