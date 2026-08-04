#include "game.hpp"
#include <iostream>

pos posKing(square *T, turn camp) // cette fonction me permettre de reperer la position du roi apres chaque test de coup
{
    pos p;
    p.lig = 0, p.col = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if ((camp == noir && T[i * 8 + j] == K_noir) || (camp == blanc && T[i * 8 + j] == K_blanc))
            {
                p.lig = i, p.col = j;
                return p;
            }
    return p;
}

void copieTab(square *T, square *T2)
{
    for (int i = 0; i < 64; i++)
    {
        T[i] = T2[i];
    }
}

bool verifBouger(Game G)
// cette fonction permettra de voir si ya une piece pouvant bouger disponible ou pas dans la fonction **choose_mouvement_human(Game *G)**
{
    for (int i = 0; i < 64; i++)
    {
        if (G.T2[i] == 6)
            return true;
    }
    return false;
}

void choixMask(Game G) // une fonction qui prendra en charge la selection de masque
{
    cout << "voulez-vous visualiser les masques ? (o/n) : ";
    char choix;
    cin >> choix;
    while (choix != 'o' && choix != 'n')
    {
        cout << "Erreur! voulez-vous visualiser les masques ? (o/n) :";
        cin >> choix;
    }
    if (choix == 'o')
        mask_choices(G.T, G.T2, G.camp);
}

bool king_in_check(Game G)
{
    int *tab = empty_mask();
    square piece;
    if (G.camp == blanc)
        piece = K_blanc;
    else
        piece = K_noir;
    pos p2;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (G.T[i * 8 + j] == piece)
                p2.lig = i, p2.col = j;
    highlight_take_pieces(G.T, tab, p2);
    for (int i = 0; i < 64; i++)
        if (tab[i] == 7)
        {
            delete[] tab;
            return true;
        }
    delete[] tab;
    return false;
}

bool choose_mouvement_king_in_check_computer(Game *G, int *T)
{
    clear_mask(T);
    square *tab3 = empty();
    copieTab(tab3, G->T); // il sera stocke jusqu'a la fin de la fonction afin de remettre le jeu en son etat apres modification.
    int *tab2 = empty_mask();
    int *tab4 = empty_mask();
    pos p2;
    pos p3;
    turn a; // variable qui va contenir la couleur de piece en jeu
    if (G->camp == blanc)
        a = blanc;
    else
        a = noir;
    highlight_movable_pieces(G->T, tab2, a);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (tab2[i * 8 + j] == 6)
            {
                p2.lig = i, p2.col = j;
                possible_move(G->T, tab4, p2);
                for (int b = 0; b < 8; b++)
                    for (int c = 0; c < 8; c++)
                        if (tab4[b * 8 + c] == 4)
                        {
                            p3.lig = b, p3.col = c;
                            move_piece(G->T, p2, p3);
                            if (!king_in_check(*G))
                            {
                                set_mask(T, i, j, 10);
                                set_mask(T, b, c, 11);
                            }
                            copieTab(G->T, tab3);
                        }
            }
    delete[] tab3;
    delete[] tab2;
    delete[] tab4;
    for (int i = 0; i < 64; i++)
        if (T[i] == 11)
            return true;
    return false;
}

bool test_run2(Game G, int i, int i2, bool *mat) // pour l'ordinateur.
{
    int *T = empty_mask();
    if (king_in_check(G))
        if (choose_mouvement_king_in_check_computer(&G, T))
        {
            if (T[i] != 10 || T[i2] != 11)
            {
                delete[] T;
                return false;
            }
        }
        else
            *mat = true;
    delete[] T;
    return true;
}

bool verifMat2(Game G, int i, int i2, bool mat)
{
    mat = false;
    bool a = test_run2(G, i, i2, &mat);
    return mat;
}

bool test_run(Game G, string casee, string caseeAr, bool *mat)
{
    int *T = empty_mask();
    clear_mask(T);
    if (casee.length() != 2 || casee[0] < 'a' || casee[0] > 'h' || casee[1] - '0' < 1 || casee[1] - '0' > 8)
    {
        // cas[i]-'0' donne la valeur de l'entier
        delete[] T;
        return false;
    }
    pos p;
    p.lig = (casee[1] - '0') - 1, p.col = casee[0] - 'a';
    if ((G.camp == blanc && (G.T[p.lig * 8 + p.col] == V || estNoir(G.T, p.lig, p.col))) || (G.camp == noir && (G.T[p.lig * 8 + p.col] == V || estBlanc(G.T, p.lig, p.col))))
    {
        delete[] T;
        return false;
    }
    possible_move(G.T, G.T2, p);
    if (!peutBouger(G.T2))
    {
        delete[] T;
        return false;
    }
    pos p2;
    p2.lig = (caseeAr[1] - '0') - 1;
    p2.col = caseeAr[0] - 'a';
    if (king_in_check(G))
        if (choose_mouvement_king_in_check_computer(&G, T))
        {
            if (T[p.lig * 8 + p.col] != 10 || T[p2.lig * 8 + p2.col] != 11)
            {
                delete[] T;
                return false;
            }
        }
        else
            *mat = true;

    if (G.T2[p2.lig * 8 + p2.col] != 4) // pour voir si la case correspond a la couleur du masque .
    {
        delete[] T;
        return false;
    }
    delete[] T;
    return true;
}

bool verifMat(Game G, string casee, string caseeAr, bool mat)
{
    mat = false;
    bool a = test_run(G, casee, caseeAr, &mat);
    return mat;
}

void choose_mouvement_human(Game *G)
{
    bool mat;
    choixMask(*G);
    cout << "Case de la piece à prendre (ex: a1,e2,...) : ";
    string casee;
    cin >> casee;
    cout << "case d'arrivee de la piece : ";
    string caseeAr;
    cin >> caseeAr;
    while (!test_run(*G, casee, caseeAr, &mat) && !verifMat(*G, casee, caseeAr, mat))
    {
        cout << "Erreur! veuillez recommencer." << endl;
        choixMask(*G);
        cout << "Case de la piece à prendre (ex: a1,e2,...) : ";
        cin >> casee;
        cout << "case d'arrivee de la piece : ";
        cin >> caseeAr;
    }
    cout << "continuer? (o/n) : ";
    char choix;
    cin >> choix;
    while (choix != 'o' && choix != 'n')
    {
        cout << "Erreur! saisir a nouveau (o/n) :";
        cin >> choix;
    }
    while (choix == 'n') // au cas ou l'utilisateur decide de reprendre , on recommence la procedure de choix de piece.
    {
        cout << "Case de la piece à prendre (ex: a1,e2,...) : ";
        cin >> casee;
        cout << "case d'arrivee de la piece : ";
        cin >> caseeAr;
        while (!test_run(*G, casee, caseeAr, &mat) && !verifMat(*G, casee, caseeAr, mat))
        {
            cout << "Erreur! veuillez recommencer." << endl;
            choixMask(*G);
            cout << "Case de la piece à prendre (ex: a1,e2,...) : ";
            cin >> casee;
            cout << "case d'arrivee de la piece : ";
            cin >> caseeAr;
        }
        if (verifMat(*G, casee, caseeAr, mat))
        {
            if (G->camp == blanc)
                G->gagnant = noir;
            else
                G->gagnant = blanc;
            return;
        }
        cout << "continuer? (o/n) : ";
        cin >> choix;
    }
    pos p;
    p.lig = (casee[1] - '0') - 1;
    p.col = casee[0] - 'a';
    pos p2;
    p2.lig = (caseeAr[1] - '0') - 1;
    p2.col = caseeAr[0] - 'a';
    move_piece(G->T, p, p2);
    if ((!G->roiblancbouge && G->T[p2.lig * 8 + p2.col] == K_blanc) || (!G->roinoirbouge && G->T[p2.lig * 8 + p2.col] == K_noir))
    {
        if (p.col - p2.col == 2 || p2.col - p.col == 2)
        {
            pos p3, p4;
            p3.lig = p2.lig;
            p4.lig = p2.lig;
            if (p2.col == 6)
            {
                if ((G->T[p2.lig * 8 + p2.col] == K_blanc && !G->tourblancdroitebouge) || (G->T[p2.lig * 8 + p2.col] == K_noir && !G->tournoirdroitebouge))
                {
                    p3.col = 7;
                    p4.col = 5;
                    move_piece(G->T, p3, p4); // On deplace la tour
                }
            }
            else
            {
                if (p2.col == 2)
                {
                    if ((G->T[p2.lig * 8 + p2.col] == K_blanc && !G->tourblancgauchebouge) || (G->T[p2.lig * 8 + p2.col] == K_noir && !G->tournoirgauchebouge))
                    {
                        p3.col = 0;
                        p4.col = 3;
                        move_piece(G->T, p3, p4); // On deplace la tour
                    }
                }
            }
        }
    }
}

void one_run_human(Game *G)
{
    choose_mouvement_human(G);
    print_board(G->T); // pour afficher l'etat du plateau de jeu
    if (G->gagnant != rien)
        return;
    if (G->camp == blanc)
        G->camp = noir;
    else
        G->camp = blanc;
    if (G->parti == HumainMachine)
    {
        G->joueur = machine;
    }
}

void choose_mouvement_computer(Game *G)
{
    int *tab = empty_mask();
    bool mat;
    highlight_movable_pieces(G->T, G->T2, G->camp);
    if (verifBouger(*G))
    {
        int i = rand() % 64;
        while (G->T2[i] != 6)
            i = rand() % 64;
        pos p;
        p.col = i % 8;
        p.lig = (i - p.col) / 8; // obtenu a partir de la formule d'indice de tableau 1D, i= p.lig*8 + p.col
        possible_move(G->T, tab, p);
        int i2 = rand() % 64;
        while (tab[i2] != 4)
            i2 = rand() % 64;
        while (!test_run2(*G, i, i2, &mat) && (!verifMat2(*G, i, i2, mat)))
        {
            i = rand() % 64;
            while (G->T2[i] != 6)
                i = rand() % 64;
            p.col = i % 8;
            p.lig = (i - p.col) / 8; // obtenu a partir de la formule d'indice de tableau 1D, i= p.lig*8 + p.col
            possible_move(G->T, tab, p);
            i2 = rand() % 64;
            while (tab[i2] != 4)
                i2 = rand() % 64;
        }
        if (verifMat2(*G, i, i2, mat))
        {
            if (G->camp == blanc)
                G->gagnant = noir;
            else
                G->gagnant = blanc;
            delete[] tab;
            return;
        }
        pos p2; // case d'arrivee
        p2.col = i2 % 8;
        p2.lig = (i2 - p2.col) / 8;
        move_piece(G->T, p, p2);
        if ((!G->roiblancbouge && G->T[p2.lig * 8 + p2.col] == K_blanc) || (!G->roinoirbouge && G->T[p2.lig * 8 + p2.col] == K_noir))
        {
            if (p.col - p2.col == 2 || p2.col - p.col == 2)
            {
                pos p3, p4;
                p3.lig = p2.lig;
                p4.lig = p2.lig;
                if (p2.col == 6)
                {
                    if ((G->T[p2.lig * 8 + p2.col] == K_blanc && !G->tourblancdroitebouge) || (G->T[p2.lig * 8 + p2.col] == K_noir && !G->tournoirdroitebouge))
                    {
                        p3.col = 7;
                        p4.col = 5;
                        move_piece(G->T, p3, p4); // On deplace la tour
                    }
                }
                else
                {
                    if (p2.col == 2)
                    {
                        if ((G->T[p2.lig * 8 + p2.col] == K_blanc && !G->tourblancgauchebouge) || (G->T[p2.lig * 8 + p2.col] == K_noir && !G->tournoirgauchebouge))
                        {
                            p3.col = 0;
                            p4.col = 3;
                            move_piece(G->T, p3, p4); // On deplace la tour
                        }
                    }
                }
            }
        }
    }
    delete[] tab;
}

void one_run_computer(Game *G)
{
    choose_mouvement_computer(G);
    print_board(G->T);
    if (G->gagnant != rien)
        return;
    if (G->camp == blanc)
        G->camp = noir;
    else
        G->camp = blanc;
    G->joueur = humain;
}

void one_run(Game *G)
{
    if (G->joueur == humain)
        one_run_human(G);
    else
    {
        one_run_computer(G);
    }
    if (G->T[4] != K_blanc)
        G->roiblancbouge = true; // pour savoir si le roque est applicable ou non.
    if (G->T[60] != K_noir)
        G->roinoirbouge = true;
    if (G->T[0] != R_blanc)
        G->tourblancgauchebouge = true;
    if (G->T[7] != R_blanc)
        G->tourblancdroitebouge = true;
    if (G->T[56] != R_noir)
        G->tournoirgauchebouge = true;
    if (G->T[63] != R_noir)
        G->tournoirdroitebouge = true;
    write_FEN(G->T, "FEN1.txt");
    MAJ_historique(G);
}
