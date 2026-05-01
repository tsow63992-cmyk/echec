#include "historique.hpp"
#include <iostream>
#include <fstream>

int nbreLigne(Game G)
{
    his *ptr = G.tete;
    int n = 1;
    if (ptr == NULL)
        return 0;
    while (ptr->next != NULL)
    {
        n++;
        ptr = ptr->next;
    }
    return n;
}

void MAJ_historique(Game *G)
{
    if (G->tete == NULL)
    {
        G->tete = new his;
        G->tete->next = NULL;
        G->tete->behind = NULL;
    }
    string ligne;
    ifstream fic("FEN1.txt");
    if (!(fic.is_open()))
        return;
    if (getline(fic, ligne))
    {
        his *ptr = G->tete;
        ptr->etat = ligne;
        while (getline(fic, ligne))
        {
            ptr->next = new his;
            ptr->next->behind = ptr;
            ptr = ptr->next;
            ptr->next = NULL;
            ptr->etat = ligne;
        }
        fic.close();
    }
    else
        return;
}

void play_historique(Game *G)
{
    square *Tcopie = empty();

    MAJ_historique(G);
    int n = nbreLigne(*G);
    his *ptr = G->tete;
    for (int i = 1; i < n; i++)
        ptr = ptr->next;

    cout << "Voulez-vous voir l'historique de jeu ?(o/n)";
    char choix;
    cin >> choix;
    while (choix != 'o' && choix != 'n')
    {
        cout << "ERREUR! Voulez-vous voir l'historique de jeu ?(o/n) ";
        cin >> choix;
    }
    if (choix == 'o')
    {
        cout << "taper s pour suivant , p pour precedent et n pour arreter: ";
        char choix2;
        cin >> choix2;

        while (choix2 != 'n')
        {
            if (choix2 != 's' && choix2 != 'p')
            {
                cout << "ERREUR! Taper s pour suivant , p pour precedent et n pour arreter: ";
                cin >> choix2;
            }
            if (choix2 == 'p')
            {
                if (ptr->behind == NULL)
                {
                    cout << "Vous etes au debut de l'historique! \n Taper s pour suivant , p pour precedent et n pour arreter: ";
                    cin >> choix2;
                }
                else
                {
                    n--;
                    ptr = ptr->behind;
                    read_FEN(Tcopie, "FEN1.txt", n);
                    print_board(Tcopie);
                    cout << "taper s pour suivant , p pour precedent et n pour arreter: ";
                    cin >> choix2;
                }
            }
            if (choix2 == 's')
            {
                if (ptr->next == NULL)
                {
                    cout << "Vous etes a la fin de l'historique! \n Taper s pour suivant , p pour precedent et n pour arreter: ";
                    cin >> choix2;
                }
                else
                {
                    n++;
                    ptr = ptr->next;
                    read_FEN(Tcopie, "FEN1.txt", n);
                    print_board(Tcopie);
                    cout << "taper s pour suivant , p pour precedent et n pour arreter: ";
                    cin >> choix2;
                }
            }
        }
    }
    delete[] Tcopie;
}

void backtrack_historique(Game *G)
{
    MAJ_historique(G);
    int n = nbreLigne(*G);
    his *ptr = G->tete;
    for (int i = 1; i < n; i++) // pour placer ptr a la fin de l'historique
        ptr = ptr->next;

    cout << "Voulez-vous remonter en arriere  ?(o/n)";
    char choix;
    cin >> choix;
    while (choix != 'o' && choix != 'n')
    {
        cout << "ERREUR! Voulez-vous remonter en arriere  ?(o/n) ";
        cin >> choix;
    }
    if (choix == 'o')
    {
        cout << "taper s pour suivant , p pour precedent et v pour valider: ";
        char choix2;
        cin >> choix2;

        while (choix2 != 'v')
        {
            if (choix2 != 's' && choix2 != 'p')
            {
                cout << "ERREUR! Taper s pour suivant , p pour precedent et v pour valider: ";
                cin >> choix2;
            }
            if (choix2 == 'p')
            {
                if (ptr->behind == NULL)
                {
                    cout << "Vous etes au debut du jeu \n Taper s pour suivant , p pour precedent et v pour valider: ";
                    cin >> choix2;
                }
                else
                {
                    n--;
                    ptr = ptr->behind;
                    read_FEN(G->T, "FEN1.txt", n);
                    print_board(G->T);
                    if (G->camp == blanc)
                        G->camp = noir;
                    else
                        G->camp = blanc;
                    if (G->parti == HumainMachine)
                    {
                        if (G->joueur == humain)
                            G->joueur = machine;
                        else
                            G->joueur = humain;
                    }
                    cout << "taper s pour suivant , p pour precedent et v pour valider: ";
                    cin >> choix2;
                }
            }
            if (choix2 == 's')
            {
                if (ptr->next == NULL)
                {
                    cout << "Vous etes a l'etat du jeu actuel \n Taper s pour suivant , p pour precedent et v pour valider: ";
                    cin >> choix2;
                }
                else
                {
                    n++;
                    ptr = ptr->next;
                    read_FEN(G->T, "FEN1.txt", n);
                    print_board(G->T);
                    if (G->camp == blanc)
                        G->camp = noir;
                    else
                        G->camp = blanc;
                    if (G->parti == HumainMachine)
                    {
                        if (G->joueur == humain)
                            G->joueur = machine;
                        else
                            G->joueur = humain;
                    }
                    cout << "taper s pour suivant , p pour precedent et v pour valider: ";
                    cin >> choix2;
                }
            }
        }
        write_FEN(G->T, "FEN1.txt");
        MAJ_historique(G);
    }
}
