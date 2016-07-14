#include <iostream>
#include "./includes/pen-utility.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    string op;
    while (true)
    {
        getline(cin, op);
        if (op == "exit")
            break;
        Scanner.append(op);
    }
    for (int i = 0; i < Scanner.lexemes.size(); ++i)
    {
        cout << Scanner.lexemes[i];
    }
    cout << endl;
    return 0;
}
