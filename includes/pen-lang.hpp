#ifndef PENLANG_HPP
#define PENLANG_HPP
#include "pen-interfaces.hpp"
#include <fstream>
using std :: ifstream;

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

class Package
{
public:
    string *str_val;
    long long *int_val;
    deque<Package> *seq_val;
    struct block
    {
        int l, r;
    } *block;
    Package();
};

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
        friend ostream & operator <<(ostream &fout, const TToken & rhs);
    };
    deque<string> seq_imm_str, seq_identifier;
    deque<long long> seq_imm_int;
    deque<TToken> lexemes;

    void append(const string & src);
};

ostream & operator <<(ostream &fout, const TScanner :: TToken & rhs);

class TParser
{

};
#endif // PENLANG_HPP
