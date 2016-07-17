#include "./includes/pen-utility.hpp"

Package TParser :: TProcessor_print :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    while (true)
    {
        next = Parser.execute(pos);
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
    if (title.code_seg == NULL || content.code_seg == NULL)
        Error.message("Invalid arguments specified for <procedure #def#>.");
    Parser.symbol_table[title.code_seg -> title] = TFunction(title.code_seg -> title, content.code_seg -> l, content.code_seg -> r);
    return Package(0);
}
Package TParser :: TProcessor_lambda :: proc(int &pos, deque<TScanner::TToken> &lexemes)
{
    int l = pos;
    int sign = 1;
    for (; sign != 0; ++pos)
    {
        if (lexemes[pos] == token_italian_bracket_l || lexemes[pos] == token_rect_bracket_l || lexemes[pos] == token_round_bracket_l)
        {
            ++sign;
        } else {
            if (lexemes[pos] == token_italian_bracket_r || lexemes[pos] == token_rect_bracket_r || lexemes[pos] == token_round_bracket_r)
            {
                --sign;
            }
        }
    }
    return Package("__lambda__", l, pos);
}
Package TParser :: TProcessor_arg :: proc(int & pos, deque<TScanner :: TToken> & lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    next = std :: move(Parser.execute(pos));
    pos++;
    next = Parser.get_arg(*next.int_val);
    if (next.int_val != NULL)
        return Package(*next.int_val);
    if (next.str_val != NULL)
        return Package(*next.str_val);
    if (next.seq_val != NULL)
        return Package(*next.seq_val);
    if (next.code_seg != NULL)
        return Package(next.code_seg->title, next.code_seg->l, next.code_seg->r);
    return Package();
}
Package TParser :: TProcessor_cond :: proc(int &pos, deque<TScanner::TToken> &lexemes)
{
    Package next;
    if (pos >= lexemes.size())
        return Package();
    long long ans = 0;
    next = std :: move(Parser.execute(pos));
    pos++;
    if (next.empty())
    {
        Error.message("Too few arguments specified for <procedure #?#>");
    }
    ans = *next.int_val;
    if (ans != 0)
    {
        next = std :: move(Parser.execute(pos));
        if (lexemes[pos].token_name == TScanner :: assign)
        {
            int l = pos;
            int sign = 1;
            for (pos += 2; sign != 0; ++pos)
            {
                if (lexemes[pos] == token_italian_bracket_l || lexemes[pos] == token_rect_bracket_l || lexemes[pos] == token_round_bracket_l)
                {
                    ++sign;
                } else {
                    if (lexemes[pos] == token_italian_bracket_r || lexemes[pos] == token_rect_bracket_r || lexemes[pos] == token_round_bracket_r)
                    {
                        --sign;
                    }
                }
            }
        } else {
            Parser.execute(pos);
        }
    } else {
        if (lexemes[pos].token_name == TScanner :: assign)
        {
            int l = pos;
            int sign = 1;
            for (++pos; sign != 0; ++pos)
            {
                if (lexemes[pos] == token_italian_bracket_l || lexemes[pos] == token_rect_bracket_l || lexemes[pos] == token_round_bracket_l)
                {
                    ++sign;
                } else {
                    if (lexemes[pos] == token_italian_bracket_r || lexemes[pos] == token_rect_bracket_r || lexemes[pos] == token_round_bracket_r)
                    {
                        --sign;
                    }
                }
            }
        } else {
            next = std :: move(Parser.execute(pos));
        }
        next = std :: move(Parser.execute(pos));
        if (next.empty())
        {
            --pos;
        }
    }
    if (next.int_val != NULL)
        return Package(*next.int_val);
    if (next.str_val != NULL)
        return Package(*next.str_val);
    if (next.seq_val != NULL)
        return Package(*next.seq_val);
    if (next.code_seg != NULL)
        return Package(next.code_seg->title, next.code_seg->l, next.code_seg->r);
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
        Error.message("Too few arguments specified for <procedure #-#>");
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
