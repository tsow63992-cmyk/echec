
#ifndef _types_HPP
#define _types_HPP
using namespace std;
#include <iostream>
#include <fstream>

enum square
{
    K_noir,
    Q_noir,
    R_noir,
    N_noir,
    B_noir,
    P_noir,
    K_blanc,
    Q_blanc,
    R_blanc,
    N_blanc,
    B_blanc,
    P_blanc,
    V,
    horsTab,
};

enum turn
{
    blanc,
    noir,
    rien, // n'est utile que pour la designation de gagnant.
    egalite,
};

enum participant
{
    HumainHumain,
    HumainMachine,
};

enum jouant
{
    humain,
    machine,
};

struct pos
{
    int lig;
    int col;
}; // cette structure est mise en place pour definir la position des differentes cases du tableau .

struct his
{
    string etat;
    his *behind;
    his *next;
};

struct Game
{
    square *T;
    int *T2;
    turn camp;         // pour savoir quel camp de couleur doit jouer
    participant parti; // pour savoir si ya une machine ou pas.
    jouant joueur;
    his *tete;
    int N; // nombre de coups.
    turn gagnant;
    bool roiblancbouge;
    bool roinoirbouge;
    bool tourblancdroitebouge;
    bool tourblancgauchebouge;
    bool tournoirdroitebouge;
    bool tournoirgauchebouge;
};

#endif
