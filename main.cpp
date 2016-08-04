#include <iostream>
#include "./includes/pen-utility.hpp"
using namespace std;
#ifdef _LINUX
constexpr size_t size = 1800 << 20;
char p[size];
#endif
#ifdef _WIN32
size_t size = 1800 << 20;
#endif
size_t i;
string op;
ifstream fin;
int pos = 0;
int ret_v;
int main(int argc, char *argv[])
{
//This assembly code expands the system stack space upto 1800MB. x86-64 only.
#ifdef _LINUX
    __asm__("MOVQ %0, %%RSP\n" :: "r"(p + size));
#endif
    if (argc == 1)
    {
        while (true)
        {
            getline(cin, op);
            if (op == "exit")
                break;
            Scanner.append(op);
            Scanner.proc_import();
        }
    } else {
        fin.open(argv[1], ios :: in);
        while (!fin.eof())
        {
            getline(fin, op);
            Scanner.append(op);
            Scanner.proc_import();
        }
    }
    Scanner.append("(main)");
    /*for (i = 0; i < Scanner.lexemes.size(); ++i)
    {
        cout << "Token #" << i << ":\t" << Scanner.lexemes[i] << endl;
    }
    cout << endl;
    cout << "########################Token list end#############################" << endl;
   */ Parser.rebind(Scanner.lexemes);

    while (pos < Scanner.lexemes.size())
    {
        auto p = Parser.execute(pos).int_val;
        if (p != NULL)
           ret_v = *p;
        else break;
    }
    exit(ret_v);
}
