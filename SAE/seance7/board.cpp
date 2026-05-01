#include "board.hpp"
using namespace std;
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

square *empty()
{
    square *Tab = new square[64]; // pour le tableau D1
    for (int i = 0; i < 64; i++)
    {
        Tab[i] = V;
    }
    return Tab;
}

square get_square(square T[], pos casee)
{
    if (casee.lig < 0 || casee.lig > 7 || casee.col < 0 || casee.col > 7)
        return horsTab;
    return T[casee.lig * 8 + casee.col];
}

bool set_square(square T[], pos casee, square p)
{
    if (casee.lig < 0 || casee.lig > 7 || casee.col < 0 || casee.col > 7)
        return false;
    T[casee.lig * 8 + casee.col] = p;
    return true;
}

void start(square T[])
{
    T[0] = R_blanc;
    T[1] = N_blanc;
    T[2] = B_blanc;
    T[3] = Q_blanc;
    T[4] = K_blanc;
    T[5] = B_blanc;
    T[6] = N_blanc;
    T[7] = R_blanc;
    for (int i = 0; i < 8; i++)
    {
        T[8 + i] = P_blanc;
        T[6 * 8 + i] = P_noir;
    }
    T[56] = R_noir;
    T[57] = N_noir;
    T[58] = B_noir;
    T[59] = Q_noir;
    T[60] = K_noir;
    T[61] = B_noir;
    T[62] = N_noir;
    T[63] = R_noir;
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
            T[i * 8 + j] = V;
    }
}

bool move_piece(square T[], pos caseDep, pos caseArri)
{
    square p = get_square(T, caseDep);
    if (p == horsTab || p == V)
        return false;
    if (set_square(T, caseArri, p))
    {
        T[caseDep.lig * 8 + caseDep.col] = V;
        return true;
    }
    return false;
}

void write_FEN(square T[], string fichier)
{
    string FEN = "";
    char conv[13] = {'k', 'q', 'r', 'n', 'b', 'p', 'K', 'Q', 'R', 'N', 'B', 'P', '-'};
    int n;
    int compteur;
    for (int i = 8; i > 0; i--)
    {
        int j = 0;
        while (j < 8)
        {
            if (T[(i - 1) * 8 + j] == V)
            {
                n = j;
                compteur = 0;
                while (T[(i - 1) * 8 + n] == V && n < 8)
                {
                    n += 1;
                    compteur += 1;
                }
                char c = '0' + compteur;
                FEN += c;
                j = n;
            }
            else
            {
                FEN += conv[T[(i - 1) * 8 + j]];
                j++;
            }
        }
        if (i != 1)
            FEN += '/';
    }
    ofstream fic(fichier, ios::app);
    if (fic)
    {
        fic << FEN << endl;
        fic.close();
    }
}

square conver(char ch)
{
    if (ch == 'r')
        return R_noir;
    if (ch == 'n')
        return N_noir;
    if (ch == 'b')
        return B_noir;
    if (ch == 'q')
        return Q_noir;
    if (ch == 'k')
        return K_noir;
    if (ch == 'R')
        return R_blanc;
    if (ch == 'N')
        return N_blanc;
    if (ch == 'B')
        return B_blanc;
    if (ch == 'Q')
        return Q_blanc;
    if (ch == 'K')
        return K_blanc;
    if (ch == 'p')
        return P_noir;
    if (ch == 'P')
        return P_blanc;
    return V;
}

void read_FEN(square T[], string fichier, int ligne)
{
    for (int i = 0; i < 64; i++)
    {
        T[i] = V;
    }
    ifstream fic(fichier);
    string FEN = "";
    string etape;
    if (fic)
    {
        for (int a = 0; a < ligne; a++)
        {
            getline(fic, etape);
        }
        FEN = etape;
    }
    int i = 0;
    int j = 7;
    int col = 0;
    while (i < FEN.length())
    {
        if (FEN[i] == '/')
        {
            i++;
            j--;
            col = 0;
        }
        else
        {
            if (conver(FEN[i]) == V)
            {
                int tmp = FEN[i] - '0';
                for (int c = col; c < (col + tmp); c++)
                {
                    T[j * 8 + c] = V;
                }
                i++;
                col += tmp;
            }
            else
            {
                T[j * 8 + col] = conver(FEN[i]);
                i++;
                col++;
            }
        }
    }
}
