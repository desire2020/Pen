#include "./includes/pen-utility.hpp"

Package TParser :: TProcessor_print :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    while (true)
    {
        next = std :: move(Parser.execute(pos));
        pos++;
        if (next.empty())
        {
            --pos;
            break;
        }
        std :: cout << next;
        std :: cout.flush();
    }
    return Package(0);
}
Package TParser :: TProcessor_def :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package title;
    Package content;
    if (pos >= lexemes.size())
        return Package();
    title = std :: move(Parser.execute(pos));
    pos++;
    content = std :: move(Parser.execute(pos));
    pos++;
    if (title.str_val == NULL || content.code_seg == NULL)
        Error.message("Invalid arguments specified for <procedure #def#>.");
    Parser.symbol_table[*title.str_val] = TFunction(*title.str_val, content.code_seg -> l, content.code_seg -> r);
    return Package(0);
}
Package TParser :: TProcessor_add :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    long long ans = 0;
    while (true)
    {
        next = std :: move(Parser.execute(pos));
        pos++;
        if (next.empty())
        {
            --pos;
            break;
        }
        ans += *next.int_val;
    }
    return Package(ans);
}
Package TParser :: TProcessor_sub :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    long long ans = 0;
    next = std :: move(Parser.execute(pos));
    pos++;
    if (next.empty())
    {
        Error.message("Too few arguments specified for <procedure #+#>");
    }
    ans = *next.int_val;
    while (true)
    {
        next = std :: move(Parser.execute(pos));
        pos++;
        if (next.empty())
        {
            --pos;
            break;
        }
        ans -= *next.int_val;
    }
    return Package(ans);
}
Package TParser :: TProcessor_mul :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    long long ans = 1;
    while (true)
    {
        next = std :: move(Parser.execute(pos));
        pos++;
        if (next.empty())
        {
            --pos;
            break;
        }
        ans *= *next.int_val;
    }
    return Package(ans);
}
Package TParser :: TProcessor_div :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    long long ans = 0;
    next = std :: move(Parser.execute(pos));
    pos++;
    if (next.empty())
    {
        Error.message("Too few arguments specified for <procedure #+#>");
    }
    ans = *next.int_val;
    while (true)
    {
        next = std :: move(Parser.execute(pos));
        pos++;
        if (next.empty())
        {
            --pos;
            break;
        }
        ans /= *next.int_val;
    }
    return Package(ans);
}
