#ifndef PENINTERFACES_HPP
#define PENINTERFACES_HPP
#include <deque>
#include <string>
#include <iostream>
#include <cstddef>
#include <stack>

using std :: deque;
using std :: string;
using std :: istream;
using std :: ostream;
using std :: stack;

class TScanner;
class TParser;
class TFile;
class TError;
extern TError Error;
extern TScanner Scanner;
extern TParser Parser;
extern TFile File;


const size_t _round_quote_l   = 0;
const size_t _round_quote_r   = 1;
const size_t _rect_quote_l    = 2;
const size_t _rect_quote_r    = 3;
const size_t _italian_quote_l = 4;
const size_t _italian_quote_r = 5;

#endif // PENINTERFACES_HPP
