#include "./includes/pen-utility.hpp"

void TError :: TMessage :: operator()(const string & _details)
{
    std :: cout << _details << std :: endl;
    exit(0);
}
void TError :: TDebugMessage :: operator ()(const string & _details)
{
    std :: cout << _details << std :: endl;
}

TScanner :: TToken :: TToken() {}
TScanner :: TToken :: TToken(TToken_name _token_name, size_t _attribute_value) : token_name(_token_name), attribute_value(_attribute_value) {}

string TScanner :: TToolkit :: str(long long x)
{
    if (x == 0)
        return "0";
    if (x < 0)
        return "-" + str(-x);
    string ans;
    ans = "";
    while (x > 0)
    {
        ans = ((char)(x % 10 + '0')) + ans;
        x /= 10;
    }
    return ans;
}

long long TScanner :: TToolkit :: val(const std::__cxx11::string &x)
{
    if (x == "" || x == "0")
        return 0;
    if (x[0] == '-')
        return -val(x.substr(1, x.length()));
    long long ans = 0;
    if (x[0] != '0')
    {
        for (int i = 0; i <= x.length() - 1; ++i)
        {
            if (x[i] > '9' || x[i] < '0')
                Error.message("Invalid immediate number \"" + x + "\"");
            ans *= 10;
            ans += x[i] - '0';
        }
        return ans;
    } else {
        if (x[1] == 'x')
        {
            for (int i = 2; i <= x.length() - 1; ++i)
            {
                if (x[i] <= '9' && x[i] >= '0')
                {
                    ans *= 16;
                    ans += x[i] - '0';
                } else {
                    if (x[i] >= 'a' && x[i] <= 'f')
                    {
                        ans *= 16;
                        ans += x[i] - 'a' + 10;
                    } else {
                        if (x[i] >= 'A' && x[i] <= 'F')
                        {
                            ans *= 16;
                            ans += x[i] - 'A' + 10;
                        } else {
                            Error.message("Invalid immediate number \"" + x + "\"");
                        }
                    }
                }
            }
        } else {
            for (int i = 1; i <= x.length() - 1; ++i)
            {
                if (x[i] <= '7' && x[i] >= '0')
                {
                    ans *= 8;
                    ans += x[i] - '0';
                } else {
                    Error.message("Invalid immediate number \"" + x + "\"");
                }
            }
        }
    }
}
string TScanner :: TToolkit :: eschar_reinterpret(const std::__cxx11::string &src)
{
    string new_cp;
    for (int i = 0; i < src.length(); ++i)
    {
        if (src[i] != '\\')
        {
            new_cp += src[i];
        } else {
            ++i;
            if (i >= src.length())
            {
                Error.message("Invalid escape character occured.");
                return src;
            }
            switch (src[i])
            {
                case 'n' :
                    new_cp += '\n';
                break;
                case 't' :
                    new_cp += '\t';
                break;
                case '\\' :
                    new_cp += '\\';
                break;
                case '0' :
                    new_cp += '\0';
                break;
                case '\"' :
                    new_cp += '\"';
                break;
                case '\'' :
                    new_cp += '\'';
                break;
                case 'r' :
                    new_cp += '\r';
                break;
                case 'v' :
                    new_cp += '\v';
                break;
            }
        }
    }
    return new_cp;
}

void TScanner :: append(const std::__cxx11::string &src)
{
    int p = 0, last_p = 0;
    string symbol;
    while (last_p < src.length())
    {
        while (p < src.length()
            && src[p] != ' '
            && src[p] != '\t'
            && src[p] != '('
            && src[p] != ')'
            && src[p] != '['
            && src[p] != ']'
            && src[p] != '{'
            && src[p] != '}'
            && src[p] != '\"') ++p;
        symbol = src.substr(last_p, p - last_p);
        if (src[last_p] == '(')
        {
            ++p;
            lexemes.push_back(TToken(assign, _round_quote_l));
        } else
            if (src[last_p] == ')')
            {
                ++p;
                lexemes.push_back(TToken(assign, _round_quote_r));
            } else
                if (src[last_p] == '[')
                {
                    ++p;
                    lexemes.push_back(TToken(assign, _rect_quote_l));
                } else
                    if (src[last_p] == ']')
                    {
                        ++p;
                        lexemes.push_back(TToken(assign, _rect_quote_r));
                    } else
                        if (src[last_p] == '{')
                        {
                            ++p;
                            lexemes.push_back(TToken(assign, _italian_quote_l));
                        } else
                            if (src[last_p] == '}')
                            {
                                ++p;
                                lexemes.push_back(TToken(assign, _italian_quote_r));
                            } else
                                if (src[last_p] == '\"')
                                {
                                    ++p;
                                    while (p < src.length() && src[p] != '\"') ++p;
                                    if (p >= src.length())
                                        Error.message("Fatal : Quote mismatch.");
                                    ++last_p;
                                    seq_imm_str.push_back(tools.eschar_reinterpret(src.substr(last_p, p - last_p)));
                                    lexemes.push_back(TToken(immediate_str, seq_imm_str.size() - 1));
                                    ++p;
                                } else
                                    if (symbol == "" || symbol == " " || symbol == "\t")
                                    {
                                        ++p;
                                    } else
                                        if (symbol[0] >= '0' && symbol[0] <= '9')
                                        {
                                            seq_imm_int.push_back(tools.val(symbol));
                                            lexemes.push_back(TToken(immediate_int, seq_imm_int.size() - 1));
                                        } else {
                                            seq_identifier.push_back(symbol);
                                            lexemes.push_back(TToken(id, seq_identifier.size() - 1));
                                        }
        last_p = p;
    }
}


void TFile :: fopen(const std::__cxx11::string &path)
{
    ifstream fin(path.c_str());
    string op;
    while (!fin.eof())
    {
        std :: getline(fin, op);
        inside.push_back(op);
    }
    fin.close();
}
void TFile :: fopen(std::istream &src)
{
    string op;
    while (!src.eof())
    {
        std :: getline(src, op);
        inside.push_back(op);
    }
}


Package :: Package() : int_val(NULL), str_val(NULL), seq_val(NULL), block(NULL) {}


ostream & operator <<(ostream &fout, const TScanner :: TToken & rhs)
{
    switch(rhs.token_name)
    {
        case TScanner :: id :
            fout << "<identifier #" << Scanner.seq_identifier[rhs.attribute_value] << "#> ";
        break;
        case TScanner :: immediate_int :
            fout << "<immediate number " << Scanner.seq_imm_int[rhs.attribute_value] << "> ";
        break;
        case TScanner :: immediate_str :
            fout << "<immediate str \"" << Scanner.seq_imm_str[rhs.attribute_value] << "\"> ";
        break;
        case TScanner :: assign :
            fout << "<assign ";
            switch (rhs.attribute_value)
            {
                case _round_quote_l :
                    fout << "\"(\"";
                break;
                case _round_quote_r :
                    fout << "\")\"";
                break;
                case _rect_quote_l :
                    fout << "\"[\"";
                break;
                case _rect_quote_r :
                    fout << "\"]\"";
                break;
                case _italian_quote_l :
                    fout << "\"{\"";
                break;
                case _italian_quote_r :
                    fout << "\"}\"";
                break;
            }
            fout << "> ";
        break;
    }
}
