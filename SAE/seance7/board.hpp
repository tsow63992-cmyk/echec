#ifndef _board_HPP
#define _board_HPP
#include "types.hpp"
#include <string>
using namespace std;

square *empty();

square get_square(square T[], pos casee);

bool set_square(square T[], pos casee, square p);

void start(square T[]);

bool move_piece(square T[], pos caseDep, pos caseArri);

void write_FEN(square T[], string fichier);

void read_FEN(square T[], string fichier, int ligne);

square conver(char ch);

#endif