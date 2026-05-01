#ifndef _game_HPP
#define _game_HPP
#include "historique.hpp"

pos posKing(square *T, turn camp);
bool verifBouger(Game G);
void choixMask(Game G);
void copieTab(square *T, square *T2);
bool test_run(Game G, string casee, string caseeAr, bool *mat);
bool test_run2(Game G, int i, int i2, bool *mat);
void choose_mouvement_human(Game *G);
void one_run_human(Game *G);
void choose_mouvement_computer(Game *G);
void one_run_computer(Game *G);
void one_run(Game *G);
bool king_in_check(Game G);
bool choose_mouvement_king_in_check_computer(Game *G, int *T);
bool verifMat2(Game G, int i, int i2, bool mat);
bool verifMat(Game G, string casee, string caseeAr, bool mat);

#endif