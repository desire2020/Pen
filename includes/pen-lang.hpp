#ifndef PENLANG_HPP
#define PENLANG_HPP
#include "pen-interfaces.hpp"
#include <fstream>
using std :: ifstream;
using std :: istream;
using std :: ostream;

class TError
{
public:
    class TMessage
    {
    public:
        void operator()(const string & _details);
    } message;
    class TDebugMessage
    {
    public:
        void operator()(const string &_details);
    } debug;
};

class TFile
{
public:
    void fopen(const string & path);
    void fopen(istream & src);
    deque<string> inside;
};
class TFunction
{
public:
    string title;
    int l, r;
    TFunction();
    TFunction(const string & _title, int _l, int _r);
    TFunction(int _l, int _r);
};

class Package
{
public:
    string *str_val;
    long long *int_val;
    deque<Package> *seq_val;
    TFunction *code_seg;
    Package();
    Package(const Package & rhs);
    Package(Package && rhs);
    Package(const string & _str);
    Package(long long _int);
    Package(const TSeq_arg & _seq);
    Package(TSeq_arg && _seq);
    Package(const string & _title, int _l, int _r);
    Package(int _l, int _r);
    ~Package();
    Package & operator =(const Package & rhs);
    Package & operator =(Package && rhs);
    bool empty() const;
};

ostream & operator <<(ostream &fout, const Package & rhs);

class TScanner
{
public:
    class TToolkit
    {
    public:
        string str(long long x);
        long long val(const string & x);
        string eschar_reinterpret(const string & src);
    } tools;

    enum TToken_name
    {
        id, immediate_int, immediate_str, assign
    };
    class TToken
    {
    public:
        TToken_name token_name;
        size_t attribute_value;
        TToken();
        TToken(TToken_name _token_name, size_t _attribute_value);
        bool operator==(const TToken & rhs) const;
        friend ostream & operator <<(ostream &fout, const TToken & rhs);
    };

    deque<string> seq_imm_str, seq_identifier;
    deque<long long> seq_imm_int;
    deque<TToken> lexemes;

    void append(const string & src);
};
const TScanner :: TToken token_round_bracket_l = TScanner :: TToken(TScanner :: assign, _round_bracket_l);
const TScanner :: TToken token_round_bracket_r = TScanner :: TToken(TScanner :: assign, _round_bracket_r);
const TScanner :: TToken token_rect_bracket_l = TScanner :: TToken(TScanner :: assign, _rect_bracket_l);
const TScanner :: TToken token_rect_bracket_r = TScanner :: TToken(TScanner :: assign, _rect_bracket_r);
const TScanner :: TToken token_italian_bracket_l = TScanner :: TToken(TScanner :: assign, _italian_bracket_l);
const TScanner :: TToken token_italian_bracket_r = TScanner :: TToken(TScanner :: assign, _italian_bracket_r);

#define DEF(x) class x : public TProcessor\
               { \
                    Package proc(int & pos, deque<TScanner :: TToken> & lexemes); \
               }

ostream & operator <<(ostream &fout, const TScanner :: TToken & rhs);

class TParser
{
public:
    class TProcessor;
    class TProcessor_print;
    class TProcessor_def;
    class TProcessor_add;
    class TProcessor_sub;
    class TProcessor_mul;
    class TProcessor_div;
protected:
    deque<TScanner :: TToken> * generated_tokens;
    unordered_map<string, TFunction> symbol_table;
    unordered_map<string, TProcessor *> keyword_vtable;
    deque<TSeq_arg> arg_stack;
public:
    class TProcessor
    {
    public:
        virtual Package proc(int & pos, deque<TScanner :: TToken> & lexemes) = 0;
    };

    DEF(TProcessor_print);
    DEF(TProcessor_def);
    DEF(TProcessor_add);
    DEF(TProcessor_sub);
    DEF(TProcessor_mul);
    DEF(TProcessor_div);
    TParser();
    ~TParser();
    Package execute(int & pos);
    void rebind(deque<TScanner :: TToken> & target);
};
#endif // PENLANG_HPP
