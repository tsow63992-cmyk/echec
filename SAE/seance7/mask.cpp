// l'indentation est faite apres chaque sauvegarde grace a une extension de vscode

#include "mask.hpp"
#include <iostream>
int *empty_mask()
{
    int *T = new int[64];
    for (int i = 0; i < 64; i++)
    {
        T[i] = 0;
    }
    return T;
}

void clear_mask(int *T)
{
    for (int i = 0; i < 64; i++)
    {
        T[i] = 0;
    }
}

int get_mask(int *T, pos p)
{
    return T[(p.lig) * 8 + p.col];
}

void set_mask(int *T, int i, int j, int val)
{
    T[i * 8 + j] = val;
}

bool estNoir(square *T, int i, int j) // pour verifier si la piece est noire
{
    if (T[i * 8 + j] == N_noir || T[i * 8 + j] == Q_noir || T[i * 8 + j] == K_noir || T[i * 8 + j] == P_noir || T[i * 8 + j] == R_noir || T[i * 8 + j] == B_noir)
        return true;
    return false;
}

bool estBlanc(square *T, int i, int j) // pour verifier si la piece est blanche
{
    if (T[i * 8 + j] == N_blanc || T[i * 8 + j] == Q_blanc || T[i * 8 + j] == K_blanc || T[i * 8 + j] == P_blanc || T[i * 8 + j] == R_blanc || T[i * 8 + j] == B_blanc)
        return true;
    return false;
}

bool estEnnemi(square *T, int i, int j, pos p) // pour verifier si 2 pieces ne sont pas dans le meme camp
{
    if ((estBlanc(T, i, j) && estNoir(T, p.lig, p.col)) || (estBlanc(T, p.lig, p.col) && estNoir(T, i, j)))
        return true;
    return false;
}

bool estAllier(square *T, int i, int j, pos p) // pour verifier si 2 pieces sont dans le meme camp
{
    if ((estBlanc(T, i, j) && estBlanc(T, p.lig, p.col)) || (estNoir(T, p.lig, p.col) && estNoir(T, i, j)))
        return true;
    return false;
}

void moves_king(square *T, int *T2, pos p)
{
    int i = p.lig, k = p.lig + 1, m = p.lig - 1; // pour les lignes possibles
    int j = p.col, l = p.col + 1, n = p.col - 1; // pour les colonnes possibles
    if (k < 8 && n >= 0)
        if (T[k * 8 + n] == V || estEnnemi(T, k, n, p))
            set_mask(T2, k, n, 4);
    if (k < 8)
        if (T[k * 8 + j] == V || estEnnemi(T, k, j, p))
            set_mask(T2, k, j, 4);
    if (k < 8 && l < 8)
        if (T[k * 8 + l] == V || estEnnemi(T, k, l, p))
            set_mask(T2, k, l, 4);
    if (l < 8)
        if (T[i * 8 + l] == V || estEnnemi(T, i, l, p))
            set_mask(T2, i, l, 4);
    if (n >= 0)
        if (T[i * 8 + n] == V || estEnnemi(T, i, n, p))
            set_mask(T2, i, n, 4);
    if (m >= 0 && n >= 0)
        if (T[m * 8 + n] == V || estEnnemi(T, m, n, p))
            set_mask(T2, m, n, 4);
    if (m >= 0)
        if (T[m * 8 + j] == V || estEnnemi(T, m, j, p))
            set_mask(T2, m, j, 4);
    if (m >= 0 && l < 8)
        if (T[m * 8 + l] == V || estEnnemi(T, m, l, p))
            set_mask(T2, m, l, 4);
}

void highlight_possible_moves_king(square *T, int *T2, pos p)
{
    if (T[(p.lig) * 8 + p.col] == K_blanc || T[(p.lig) * 8 + p.col] == K_noir)
    {
        clear_mask(T2);
        set_mask(T2, p.lig, p.col, 1);
        moves_king(T, T2, p);
    }
}

void moves_rook(square *T, int *T2, pos p)
{
    int i = p.lig, j = p.col;
    while (i + 1 < 8 && estAllier(T, i + 1, j, p) == false)
    {
        if (estEnnemi(T, i + 1, j, p))
        {
            set_mask(T2, i + 1, j, 4);
            i = 7;
        }
        else
        {
            set_mask(T2, i + 1, j, 4);
            i++;
        }
    }
    i = p.lig;
    while (i - 1 >= 0 && estAllier(T, i - 1, j, p) == false)
    {
        if (estEnnemi(T, i - 1, j, p))
        {
            set_mask(T2, i - 1, j, 4);
            i = 0;
        }
        else
        {
            set_mask(T2, i - 1, j, 4);
            i--;
        }
    }
    i = p.lig;
    while (j + 1 < 8 && estAllier(T, i, j + 1, p) == false)
    {
        if (estEnnemi(T, i, j + 1, p))
        {
            set_mask(T2, i, j + 1, 4);
            j = 7;
        }
        else
        {
            set_mask(T2, i, j + 1, 4);
            j++;
        }
    }
    j = p.col;
    while (j - 1 >= 0 && estAllier(T, i, j - 1, p) == false)
    {
        if (estEnnemi(T, i, j - 1, p))
        {
            set_mask(T2, i, j - 1, 4);
            j = 0;
        }
        else
        {
            set_mask(T2, i, j - 1, 4);
            j--;
        }
    }
}

void highlight_possible_moves_rook(square *T, int *T2, pos p)
{
    if (T[(p.lig) * 8 + p.col] == R_blanc || T[(p.lig) * 8 + p.col] == R_noir)
    {
        clear_mask(T2);
        set_mask(T2, p.lig, p.col, 1);
        moves_rook(T, T2, p);
    }
}

void move_bishop(square *T, int *T2, pos p) // cases accessibles par le bishop blanc
{
    int i = p.lig, j = p.col;
    while (i < 7 && j < 7 && estAllier(T, i + 1, j + 1, p) == false) // en allant vers le haut-droite
    {
        if (estEnnemi(T, i + 1, j + 1, p))
        {
            set_mask(T2, i + 1, j + 1, 4);
            i = 7;
        }
        else
        {
            set_mask(T2, i + 1, j + 1, 4);
            i++;
            j++;
        }
    }
    i = p.lig, j = p.col;
    while (i < 7 && j > 0 && estAllier(T, i + 1, j - 1, p) == false) // en allant vers haut-gauche
    {
        if (estEnnemi(T, i + 1, j - 1, p))
        {
            set_mask(T2, i + 1, j - 1, 4);
            i = 7;
        }
        else
        {
            set_mask(T2, i + 1, j - 1, 4);
            i++;
            j--;
        }
    }
    i = p.lig, j = p.col;
    while (i > 0 && j > 0 && estAllier(T, i - 1, j - 1, p) == false) // en allant vers le bas-gauche
    {
        if (estEnnemi(T, i - 1, j - 1, p))
        {
            set_mask(T2, i - 1, j - 1, 4);
            i = 0;
        }
        else
        {
            set_mask(T2, i - 1, j - 1, 4);
            i--;
            j--;
        }
    }
    i = p.lig, j = p.col;
    while (i > 0 && j < 7 && estAllier(T, i - 1, j + 1, p) == false) // en allant vers le bas-droite
    {
        if (estEnnemi(T, i - 1, j + 1, p))
        {
            set_mask(T2, i - 1, j + 1, 4);
            i = 0;
        }
        else
        {
            set_mask(T2, i - 1, j + 1, 4);
            i--;
            j++;
        }
    }
}

void highlight_possible_moves_bishop(square *T, int *T2, pos p)
{
    if (T[(p.lig) * 8 + p.col] == B_blanc || T[(p.lig) * 8 + p.col] == B_noir) // pour etre sur qu'il s'agit bien du fou
    {
        clear_mask(T2);
        set_mask(T2, p.lig, p.col, 1);
        move_bishop(T, T2, p);
    }
}

void highlight_possible_moves_queen(square *T, int *T2, pos p)
{
    if (T[p.lig * 8 + p.col] == Q_blanc || T[p.lig * 8 + p.col] == Q_noir)
    {
        clear_mask(T2);
        set_mask(T2, p.lig, p.col, 1);

        // nous allons combiner les mouvement possible de la tour et du fou

        move_bishop(T, T2, p);
        moves_rook(T, T2, p);
    }
}

void move_knight(square *T, int *T2, pos p)
{
    int i = p.lig + 1, k = p.lig + 2, m = p.lig - 1, o = p.lig - 2; // pour les lignes possibles
    int j = p.col + 1, l = p.col + 2, n = p.col - 1, q = p.col - 2; // pour les colonnes possibles
    if (i < 8 && q >= 0)
        if (T[i * 8 + q] == V || estEnnemi(T, i, q, p))
            set_mask(T2, i, q, 4);
    if (k < 8 && n >= 0)
        if (T[k * 8 + n] == V || estEnnemi(T, k, n, p))
            set_mask(T2, k, n, 4);
    if (k < 8 && j < 8)
        if (T[k * 8 + j] == V || estEnnemi(T, k, j, p))
            set_mask(T2, k, j, 4);
    if (l < 8 && i < 8)
        if (T[i * 8 + l] == V || estEnnemi(T, i, l, p))
            set_mask(T2, i, l, 4);
    if (m >= 0 && l < 8)
        if (T[m * 8 + l] == V || estEnnemi(T, m, l, p))
            set_mask(T2, m, l, 4);
    if (o >= 0 && j < 8)
        if (T[o * 8 + j] == V || estEnnemi(T, o, j, p))
            set_mask(T2, o, j, 4);
    if (o >= 0 && n >= 0)
        if (T[o * 8 + n] == V || estEnnemi(T, o, n, p))
            set_mask(T2, o, n, 4);
    if (m >= 0 && q >= 0)
        if (T[m * 8 + q] == V || estEnnemi(T, m, q, p))
            set_mask(T2, m, q, 4);
}

void highlight_possible_moves_knight(square *T, int *T2, pos p)
{
    if (T[p.lig * 8 + p.col] == N_blanc || T[p.lig * 8 + p.col] == N_noir)
    {
        clear_mask(T2);
        set_mask(T2, p.lig, p.col, 1);
        move_knight(T, T2, p);
    }
}

void move_pawn(square *T, int *T2, pos p)
{
    int i = p.lig, j = p.col;
    if (estBlanc(T, i, j))
    {
        if (i == 1)
            for (int a = 2; a < 4; a++)
            {
                if (T[a * 8 + j] != V)
                    break;
                set_mask(T2, a, j, 4);
            }
        if (i + 1 < 8)
        {
            if (T[(i + 1) * 8 + j] == V)
                set_mask(T2, i + 1, j, 4);
            if (j + 1 < 8 && estEnnemi(T, i + 1, j + 1, p))
                set_mask(T2, i + 1, j + 1, 4);
            if (j - 1 >= 0 && estEnnemi(T, i + 1, j - 1, p))
                set_mask(T2, i + 1, j - 1, 4);
        }
    }
    else
    {
        if (i == 6)
            for (int a = 5; a > 3; a--)
            {
                if (T[a * 8 + j] != V)
                    break;
                set_mask(T2, a, j, 4);
            }
        if (i - 1 >= 0)
        {
            if (T[(i - 1) * 8 + j] == V)
                set_mask(T2, i - 1, j, 4);
            if (j + 1 < 8 && estEnnemi(T, i - 1, j + 1, p))
                set_mask(T2, i - 1, j + 1, 4);
            if (j - 1 >= 0 && estEnnemi(T, i - 1, j - 1, p))
                set_mask(T2, i - 1, j - 1, 4);
        }
    }
}

void highlight_possible_moves_pawn(square *T, int *T2, pos p)
{
    if (T[p.lig * 8 + p.col] == P_blanc || T[p.lig * 8 + p.col] == P_noir)
    {
        clear_mask(T2);
        set_mask(T2, p.lig, p.col, 1);
        move_pawn(T, T2, p);
    }
}

bool peutBouger(int *T) // une fonction permettant de voir si le masque confirme la possibilite de mouvement de la piece
{
    for (int i = 0; i < 64; i++)
        if (T[i] == 4)
            return true;
    return false;
}

void possible_move(square *T, int *T2, pos p)
{
    // cette me permettra de simplifier l'ecriture des prochaines fonctions .

    if (T[p.lig * 8 + p.col] == K_blanc || T[p.lig * 8 + p.col] == K_noir)
        highlight_possible_moves_king(T, T2, p);
    if (T[p.lig * 8 + p.col] == Q_blanc || T[p.lig * 8 + p.col] == Q_noir)
        highlight_possible_moves_queen(T, T2, p);
    if (T[p.lig * 8 + p.col] == N_blanc || T[p.lig * 8 + p.col] == N_noir)
        highlight_possible_moves_knight(T, T2, p);
    if (T[p.lig * 8 + p.col] == R_blanc || T[p.lig * 8 + p.col] == R_noir)
        highlight_possible_moves_rook(T, T2, p);
    if (T[p.lig * 8 + p.col] == B_blanc || T[p.lig * 8 + p.col] == B_noir)
        highlight_possible_moves_bishop(T, T2, p);
    if (T[p.lig * 8 + p.col] == P_blanc || T[p.lig * 8 + p.col] == P_noir)
        highlight_possible_moves_pawn(T, T2, p);
}

void highlight_movable_white_pieces(square *T, int *T2) // pour montrer les pieces blanches pouvant se deplacer
{
    int *Tcopie = empty_mask();

    /* ici Tcopie nous servira d'intermediaire pour remplir T2 parceque dans mes fonctions precedentes (highlight_possible_move...) T2 etait reinitialise
        a chaque utilisation .*/

    pos p;
    for (int i = 0; i < 8; i++)
    {
        p.lig = i;
        for (int j = 0; j < 8; j++)
        {
            p.col = j;
            if (T[i * 8 + j] == K_blanc)
            {
                highlight_possible_moves_king(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == Q_blanc)
            {
                highlight_possible_moves_queen(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == R_blanc)
            {
                highlight_possible_moves_rook(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == N_blanc)
            {
                highlight_possible_moves_knight(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == B_blanc)
            {
                highlight_possible_moves_bishop(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == P_blanc)
            {
                highlight_possible_moves_pawn(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
        }
    }
    delete[] Tcopie;
}

void highlight_movable_black_pieces(square *T, int *T2) // pour montrer les pieces noires pouvant se deplacer
{
    int *Tcopie = empty_mask();
    pos p;
    for (int i = 0; i < 8; i++)
    {
        p.lig = i;
        for (int j = 0; j < 8; j++)
        {
            p.col = j;
            if (T[i * 8 + j] == K_noir)
            {
                highlight_possible_moves_king(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == Q_noir)
            {
                highlight_possible_moves_queen(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == R_noir)
            {
                highlight_possible_moves_rook(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == N_noir)
            {
                highlight_possible_moves_knight(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == B_noir)
            {
                highlight_possible_moves_bishop(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
            if (T[i * 8 + j] == P_noir)
            {
                highlight_possible_moves_pawn(T, Tcopie, p);
                if (peutBouger(Tcopie))
                    set_mask(T2, i, j, 6);
            }
        }
    }
    delete[] Tcopie;
}

void highlight_movable_pieces(square *T, int *T2, turn camp)
{
    clear_mask(T2);
    if (camp == noir)
        highlight_movable_black_pieces(T, T2);
    else
        highlight_movable_white_pieces(T, T2);
}

void remplirCopie(int *T, int *T2)
{
    for (int i = 0; i < 64; i++)
        if (T2[i] == 4)
            T[i] = 4;
}

// notez que le 4 represente la couleur du masque representant les cases accessibles

void highlight_attacked_black_pieces(square *T, int *T2)
{
    int *Tcopie = empty_mask();
    /* ici Tcopie nous servira d'intermediaire pour remplir T2 parceque dans mes fonctions precedentes (highlight_possible_move...) T2 etait reinitialise
        a chaque utilisation .*/

    int *Tcopie2 = empty_mask();
    /*cette deuxieme copie servira a garder toutes les cases pouvant etre accessible par l'adversaire */

    pos p;
    for (int i = 0; i < 8; i++)
    {
        p.lig = i;
        for (int j = 0; j < 8; j++)
        {
            p.col = j;
            if (T[i * 8 + j] == K_blanc)
            {
                highlight_possible_moves_king(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == Q_blanc)
            {
                highlight_possible_moves_queen(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == R_blanc)
            {
                highlight_possible_moves_rook(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == N_blanc)
            {
                highlight_possible_moves_knight(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == B_blanc)
            {
                highlight_possible_moves_bishop(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == P_blanc)
            {
                highlight_possible_moves_pawn(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (estNoir(T, i, j))
            {
                if (Tcopie2[i * 8 + j] == 4)
                    set_mask(T2, i, j, 1);
                else
                    set_mask(T2, i, j, 2);
            }
        }
    }
    delete[] Tcopie;
    delete[] Tcopie2;
}

void highlight_attacked_white_pieces(square *T, int *T2)
{
    int *Tcopie = empty_mask();
    /* ici Tcopie nous servira d'intermediaire pour remplir T2 parceque dans mes fonctions precedentes (highlight_possible_move...) T2 etait reinitialise
        a chaque utilisation .*/

    int *Tcopie2 = empty_mask();
    /*cette deuxieme copie servira a garder toutes les cases pouvant etre accessible par l'adversaire */

    pos p;
    for (int i = 0; i < 8; i++)
    {
        p.lig = i;
        for (int j = 0; j < 8; j++)
        {
            p.col = j;
            if (T[i * 8 + j] == K_noir)
            {
                highlight_possible_moves_king(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == Q_noir)
            {
                highlight_possible_moves_queen(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == R_noir)
            {
                highlight_possible_moves_rook(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == N_noir)
            {
                highlight_possible_moves_knight(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == B_noir)
            {
                highlight_possible_moves_bishop(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
            if (T[i * 8 + j] == P_noir)
            {
                highlight_possible_moves_pawn(T, Tcopie, p);
                remplirCopie(Tcopie2, Tcopie);
            }
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (estBlanc(T, i, j))
            {
                if (Tcopie2[i * 8 + j] == 4)
                    set_mask(T2, i, j, 1);
                else
                    set_mask(T2, i, j, 2);
            }
        }
    }
    delete[] Tcopie;
    delete[] Tcopie2;
}

void highlight_attacked_pieces(square *T, int *T2, turn camp)
{
    clear_mask(T2);
    if (camp == blanc)
        highlight_attacked_black_pieces(T, T2);
    else
        highlight_attacked_white_pieces(T, T2);
}

void take_piece(square *T, int *T2, pos p)
{
    int *Tcopie = empty_mask();
    pos p2;
    for (int i = 0; i < 8; i++)
    {
        p2.lig = i;
        for (int j = 0; j < 8; j++)
        {
            p2.col = j;
            if (estEnnemi(T, i, j, p))
            {
                possible_move(T, Tcopie, p2);
                if (Tcopie[p.lig * 8 + p.col] == 4)
                    set_mask(T2, i, j, 7);
            }
        }
    }
    delete[] Tcopie;
}

void highlight_take_pieces(square *T, int *T2, pos p)
{
    clear_mask(T2);
    set_mask(T2, p.lig, p.col, 1);
    take_piece(T, T2, p);
}
