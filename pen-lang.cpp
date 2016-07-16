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
bool TScanner :: TToken :: operator == (const TScanner :: TToken & rhs) const
{
    return token_name == rhs.token_name && attribute_value == rhs.attribute_value;
}

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
            lexemes.push_back(TToken(assign, _round_bracket_l));
        } else
            if (src[last_p] == ')')
            {
                ++p;
                lexemes.push_back(TToken(assign, _round_bracket_r));
            } else
                if (src[last_p] == '[')
                {
                    ++p;
                    lexemes.push_back(TToken(assign, _rect_bracket_l));
                } else
                    if (src[last_p] == ']')
                    {
                        ++p;
                        lexemes.push_back(TToken(assign, _rect_bracket_r));
                    } else
                        if (src[last_p] == '{')
                        {
                            ++p;
                            lexemes.push_back(TToken(assign, _italian_bracket_l));
                        } else
                            if (src[last_p] == '}')
                            {
                                ++p;
                                lexemes.push_back(TToken(assign, _italian_bracket_r));
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

TFunction :: TFunction() : title(""), l(0), r(0) {}
TFunction :: TFunction(const std::__cxx11::string &_title, int _l, int _r) : title(_title), l(_l), r(_r) {}
TFunction :: TFunction(int _l, int _r) : title(""), l(_l), r(_r) {}

Package :: Package() : int_val(NULL), str_val(NULL), seq_val(NULL), code_seg(NULL) {}
Package :: Package(const Package &rhs)
{
    Package();
    if (rhs.int_val != NULL)
        int_val = new long long(*(rhs.int_val));
    if (rhs.str_val != NULL)
        str_val = new string(*(rhs.str_val));
    if (rhs.seq_val != NULL)
        seq_val = new TSeq_arg(*(rhs.seq_val));
    if (rhs.code_seg != NULL)
        code_seg = new TFunction(*(rhs.code_seg));
}
Package :: Package(Package && rhs)
{
    if (rhs.int_val != NULL)
        int_val = new long long(*(rhs.int_val));
    if (rhs.str_val != NULL)
        str_val = new string(*(rhs.str_val));
    if (rhs.seq_val != NULL)
        seq_val = new TSeq_arg(std :: move(*(rhs.seq_val)));
    if (rhs.code_seg != NULL)
        code_seg = new TFunction(*(rhs.code_seg));
}

Package :: Package(const std::__cxx11::string &_str)
{
    int_val = NULL;
    str_val = new string(_str);
    seq_val = NULL;
    code_seg = NULL;
}
Package :: Package(long long _int)
{
    int_val = new long long(_int);
    str_val = NULL;
    seq_val = NULL;
    code_seg = NULL;
}
Package :: Package(const TSeq_arg & _seq)
{
    int_val = NULL;
    str_val = NULL;
    seq_val = new TSeq_arg(_seq);
    code_seg = NULL;
}
Package :: Package(TSeq_arg && _seq)
{
    int_val = NULL;
    str_val = NULL;
    seq_val = new TSeq_arg(_seq);
    code_seg = NULL;
}
Package :: Package(const std::__cxx11::string &_title, int _l, int _r)
{
    int_val = NULL;
    str_val = NULL;
    seq_val = NULL;
    code_seg = new TFunction(_title, _l, _r);
}
Package & Package :: operator = (const Package & rhs)
{
    this -> ~Package();
    int_val = clone_ptr(rhs.int_val);
    str_val = clone_ptr(rhs.str_val);
    seq_val = clone_ptr(rhs.seq_val);
    code_seg = clone_ptr(rhs.code_seg);
    return *this;
}
Package & Package :: operator = (Package && rhs)
{
    this -> ~Package();
    int_val = move_ptr(rhs.int_val);
    str_val = move_ptr(rhs.str_val);
    seq_val = move_ptr(rhs.seq_val);
    code_seg = move_ptr(rhs.code_seg);
    return *this;
}
Package :: Package(int _l, int _r)
{
    int_val = NULL;
    str_val = NULL;
    seq_val = NULL;
    code_seg = new TFunction(_l, _r);
}
Package :: ~Package()
{
    if (int_val != NULL)
        delete int_val;
    if (str_val != NULL)
        delete str_val;
    if (seq_val != NULL)
        delete seq_val;
    if (code_seg != NULL)
        delete code_seg;
}
bool Package :: empty() const
{
    return int_val == NULL && str_val == NULL && seq_val == NULL && code_seg == NULL;
}
ostream & operator <<(ostream & fout, const Package & rhs)
{
    if (rhs.int_val != NULL)
        fout << *rhs.int_val;
    if (rhs.str_val != NULL)
        fout << *rhs.str_val;
    if (rhs.seq_val != NULL)
    {
        deque<Package> & tg = *rhs.seq_val;
        for (auto i = tg.begin(); i != tg.end(); ++i)
        {
            fout << *i;
        }
    }
    if (rhs.code_seg != NULL)
    {
        fout << "<#procedure# " << rhs.code_seg -> title << ">";
    }
    return fout;
}


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
                case _round_bracket_l :
                    fout << "\"(\"";
                break;
                case _round_bracket_r :
                    fout << "\")\"";
                break;
                case _rect_bracket_l :
                    fout << "\"[\"";
                break;
                case _rect_bracket_r :
                    fout << "\"]\"";
                break;
                case _italian_bracket_l :
                    fout << "\"{\"";
                break;
                case _italian_bracket_r :
                    fout << "\"}\"";
                break;
            }
            fout << "> ";
        break;
    }
    return fout;
}




TParser :: TParser()
{
    keyword_vtable["print"] = new TProcessor_print();
    keyword_vtable["def"]   = new TProcessor_def();
    keyword_vtable["+"]     = new TProcessor_add();
    keyword_vtable["-"]     = new TProcessor_sub();
    keyword_vtable["*"]     = new TProcessor_mul();
    keyword_vtable["/"]     = new TProcessor_div();
}
TParser :: ~TParser()
{
    for (auto i = keyword_vtable.begin(); i != keyword_vtable.end(); ++i)
    {
        delete (i -> second);
    }
}

void TParser :: rebind(deque<TScanner :: TToken> &target)
{
    generated_tokens = &target;
}

Package TParser :: execute(int & pos)
{
    deque<TScanner :: TToken> & lst(*generated_tokens);
    switch (lst[pos].token_name)
    {
        case TScanner :: assign :
            if (lst[pos] == token_round_bracket_l || lst[pos] == token_rect_bracket_l || lst[pos] == token_italian_bracket_l)
            {
                auto tmp = execute(++pos);
                if (tmp.code_seg == NULL || tmp.code_seg -> title == "")
                   Error.message("Invalid expression occured.");
                string title = tmp.code_seg -> title;
                auto target = keyword_vtable.find(title);
                if (target != keyword_vtable.end())
                {
                    TProcessor * op = target -> second;
                    return op -> proc(++pos, lst);
                } else {
                    TSeq_arg in_pending;
                    Package next;
                    while (true)
                    {
                        next = std :: move(execute(++pos));
                        if (next.empty())
                            break;
                        in_pending.push_back(std :: move(next));
                    }
                    arg_stack.push_back(std :: move(in_pending));
                    auto tg = symbol_table.find(title);
                    if (tg == symbol_table.end())
                        Error.message("Invalid operator #" + title + "# found.");
                    int p = tg -> second.l;
                    return execute(p);
                }
            } else {
                return Package();
            }
        break;
        case TScanner :: id :
            return Package(Scanner.seq_identifier[lst[pos].attribute_value], 0, 0);
        break;
        case TScanner :: immediate_int :
            return Package(Scanner.seq_imm_int[lst[pos].attribute_value]);
        break;
        case TScanner :: immediate_str :
            return Package(Scanner.seq_imm_str[lst[pos].attribute_value]);
        break;
    }
    return Package();
}
