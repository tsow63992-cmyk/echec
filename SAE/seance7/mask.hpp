#ifndef _mask_HPP
#define _mask_HPP
#include "board.hpp"
#include "types.hpp"
using namespace std;

int *empty_mask();
void clear_mask(int *T);
int get_mask(int *T, pos p);
void set_mask(int *T, int i, int j, int val);
bool estNoir(square *T, int i, int j);
bool estBlanc(square *T, int i, int j);
bool estEnnemi(square *T, int i, int j, pos p2);
bool estAllier(square *T, int i, int j, pos p2);
void moves_king(square *T, int *T2, pos p);
void moves_rook(square *T, int *T2, pos p);
void move_bishop(square *T, int *T2, pos p);
void move_knight(square *T, int *T2, pos p);
void move_pawn(square *T, int *T2, pos p);
bool peutBouger(int *T);
void remplirCopie(int *T, int *T2);
void possible_move(square *T, int *T2, pos p);
void highlight_movable_white_pieces(square *T, int *T2);
void highlight_movable_black_pieces(square *T, int *T2);
void highlight_possible_moves_pawn(square *T, int *T2, pos p);
void highlight_possible_moves_king(square *T, int *T2, pos p);
void highlight_possible_moves_rook(square *T, int *T2, pos p);
void highlight_possible_moves_bishop(square *T, int *T2, pos p);
void highlight_possible_moves_queen(square *T, int *T2, pos p);
void highlight_possible_moves_knight(square *T, int *T2, pos p);
void highlight_movable_pieces(square *T, int *T2, turn camp);
void highlight_attacked_pieces(square *T, int *T2, turn camp);
void highlight_take_pieces(square *T, int *T2, pos p);
#endif