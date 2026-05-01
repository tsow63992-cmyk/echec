#ifndef _view_HPP
#define _view_HPP
#include "mask.hpp"

void print_square(square t);
void print_board(square *T);
void print_board(square *T, int *T2);
void print_square_color(square t, int lig, int col);
void print_square_color(square t, int lig, int col, int *T);
void set_background(int couleur);
void set_foreground(int couleur);
void mask_choices_menu();
void mask_choices(square *T, int *T2, turn camp);
#endif