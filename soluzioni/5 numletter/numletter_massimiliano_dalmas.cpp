#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "course_lib.h"

using namespace std;

static int level;

static string unit[] = 
{
    "zero",
    "uno",
    "due",
    "tre",
    "quattro",
    "cinque",
    "sei",
    "sette",
    "otto",
    "nove"
};

static string middle[] = 
{
    "undici",
    "dodici",
    "tredici",
    "quattordici",
    "quindici",
    "sedici",
    "diciassette",
    "diciotto",
    "diciannove"
};

static string decs[] = 
{
    "dieci",
    "venti",
    "trenta",
    "quaranta",
    "cinquanta",
    "sessanta",
    "settanta",
    "ottanta",
    "novanta"
};

static string str_level[] = 
{
    "",
    "mila",
    "milioni",
    "miliardi",
    "bilioni"
};

vector<size_t> separate(size_t num)
{
    vector<size_t> v;
    if (num == 0)
    {
        v.push_back(num);
        return v;
    }
    while (num !=0)
    {
        v.push_back(num % 1000);
        num /= 1000;
    }
    reverse(v.begin(),v.end());
}

void convert_10(size_t num, string &str)
{
    if (num < 10)
    {
        str += unit[num];
        return;
    }
    else if (num > 10 && num < 20)
    {
        str += middle[num - 11];
        return;
    }
    auto d = num / 10;
    auto u = num % 10;
    if (u == 0)
    {
        str += decs[d-1];
        return;
    }
    auto tmp1 = decs[d-1];
    auto tmp2 = unit[u];
    str += tmp1;
    if (u == 1 || u == 8)
        str.pop_back();
    str += tmp2;
}

void convert__100(size_t num, string &str)
{
    if (num == 0 && level == 1)
    {
        convert_10(num,str);
        return;
    }
    auto h = num / 100;
    auto d = num % 100;
    if (h == 0) convert_10(d,str);
    else {
        if (h == 1)
            str += "cento";
        else
            str += unit[h] + "cento";
        if (d > 0)
        {
            //if (d == 8 || (d / 10) == 8)
            //    str.pop_back();
            convert_10(d,str);
        }
    }
}

void
numeri_lettere( long N, string & res ) {
    auto pieces  = separate(N);
    level        = pieces.size();
    auto lev     = level;
    bool missing = false;
    for (auto p : pieces)
    { 
        if (lev > 1 && p > 0)
        {
            if (level > 2 && lev < level && p != 0)
            {
                res += " e ";
                missing = false;
            }
            if (p == 1 && lev == 2)
                res += "mille";
            else
            {
                convert__100(p,res);
                if (lev > 2 && p == 1) res.pop_back();
                if (lev > 2) res += " ";
                res += str_level[lev - 1];
                if (p == 1 && lev > 2)
                {
                    res.pop_back();
                    switch (lev)
                    {
                        case 4:
                            res += "o";
                            break;
                        case 3:
                            res += "e";
                            break;
                        default:
                            break;
                    }
                }
            }
        } else {
            if (lev == 1) 
            {
                if (level > 1 && p != 0)
                {
                    if (missing)
                        res += " e ";
                    convert__100(p,res);
                } else if (level == 1)
                    convert__100(p,res);
            } else if (level > 2) 
                missing = true;
        }
        lev--;

    }
}
