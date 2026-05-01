#include "view.hpp"
#include <iostream>
using namespace std;

void print_square(square t)
{

    // pour l'affichage des cases avec des lettres.

    if (t == K_noir)
        cout << 'k';
    if (t == Q_noir)
        cout << 'q';
    if (t == R_noir)
        cout << 'r';
    if (t == N_noir)
        cout << 'n';
    if (t == B_noir)
        cout << 'b';
    if (t == P_noir)
        cout << 'p';
    if (t == V)
        cout << '-';
    if (t == K_blanc)
        cout << 'K';
    if (t == Q_blanc)
        cout << 'Q';
    if (t == R_blanc)
        cout << 'R';
    if (t == N_blanc)
        cout << 'N';
    if (t == B_blanc)
        cout << 'B';
    if (t == P_blanc)
        cout << 'P';
}

void set_background(int couleur)
{
    cout << "\x1b[48;5;" << couleur << "m";
};

void set_foreground(int couleur)
{
    cout << "\x1b[38;5;" << couleur << "m";
};

void print_square_color(square t, int lig, int col)
{

    /*notez que le 21 represente le bleu
    le 230 represente la couleur d'une case claire
    le 16 represente le noir pur
    le 179 represente la couleur fonce de la case */

    if ((lig + col) % 2 == 0)
        set_background(179);
    else
    {
        set_background(230);
    }
    if (t == K_noir || t == Q_noir || t == R_noir || t == N_noir || t == B_noir || t == P_noir)
        set_foreground(16);
    else
    {
        set_foreground(21);
    }
    if (t == K_noir)
        cout << "\u265A";
    if (t == Q_noir)
        cout << "\u265B";
    if (t == R_noir)
        cout << "\u265C";
    if (t == N_noir)
        cout << "\u265E";
    if (t == B_noir)
        cout << "\u265D";
    if (t == P_noir)
        cout << "\u265F";
    if (t == V)
        cout << " ";
    if (t == K_blanc)
        cout << "\u265A";
    if (t == Q_blanc)
        cout << "\u265B";
    if (t == R_blanc)
        cout << "\u265C";
    if (t == N_blanc)
        cout << "\u265E";
    if (t == B_blanc)
        cout << "\u265D";
    if (t == P_blanc)
        cout << "\u265F";
    cout << "\x1b[0m"; // pour supprimer les couleur apres affichage
}

void print_square_color(square t, int lig, int col, int *T)
{

    /*notez que le 21 represente le bleu
    le 230 represente la couleur d'une case claire
    le 16 represente le noir pur
    le 179 represente la couleur fonce de la case */
    if (T[lig * 8 + col] == 0)
    {
        if ((lig + col) % 2 == 0)
            set_background(179);
        else
        {
            set_background(230);
        }
    }
    else
    {
        set_background(T[lig * 8 + col]);
    }
    if (t == K_noir || t == Q_noir || t == R_noir || t == N_noir || t == B_noir || t == P_noir)
        set_foreground(16);
    else
    {
        set_foreground(21);
    }
    if (t == K_noir)
        cout << "\u265A";
    if (t == Q_noir)
        cout << "\u265B";
    if (t == R_noir)
        cout << "\u265C";
    if (t == N_noir)
        cout << "\u265E";
    if (t == B_noir)
        cout << "\u265D";
    if (t == P_noir)
        cout << "\u265F";
    if (t == V)
        cout << " ";
    if (t == K_blanc)
        cout << "\u265A";
    if (t == Q_blanc)
        cout << "\u265B";
    if (t == R_blanc)
        cout << "\u265C";
    if (t == N_blanc)
        cout << "\u265E";
    if (t == B_blanc)
        cout << "\u265D";
    if (t == P_blanc)
        cout << "\u265F";
    cout << "\x1b[0m"; // pour supprimer les couleur apres affichage
}

void print_board(square *T)
{
    cout << " a b c d e f g h   " << endl;
    for (int i = 8; i > 0; i--)
    {
        cout << i;
        for (int j = 0; j < 8; j++)
        {
            print_square_color(T[(i - 1) * 8 + j], i - 1, j);
            if (((i - 1) + j) % 2 == 0)
            {
                set_background(179);
                cout << " ";
                cout << "\x1b[0m";
            }
            else
            {
                set_background(230);
                cout << " ";
                cout << "\x1b[0m";
            }
        }
        cout << " " << i << endl;
    }
    cout << " a b c d e f g h   " << endl;
}

void print_board(square *T, int *T2)
{
    cout << " a b c d e f g h   " << endl;
    for (int i = 8; i > 0; i--)
    {
        cout << i;
        for (int j = 0; j < 8; j++)
        {
            print_square_color(T[(i - 1) * 8 + j], i - 1, j, T2);
            if (T2[(i - 1) * 8 + j] != 0)
            {
                set_background(T2[(i - 1) * 8 + j]);
                cout << " ";
                cout << "\x1b[0m";
            }
            else
            {
                if (((i - 1) + j) % 2 == 0)
                {
                    set_background(179);
                    cout << " ";
                    cout << "\x1b[0m";
                }
                else
                {
                    set_background(230);
                    cout << " ";
                    cout << "\x1b[0m";
                }
            }
        }
        cout << " " << i << endl;
    }
    cout << " a b c d e f g h   " << endl;
}

void mask_choices_menu()
{
    cout << "Voici les masques disponibles :\n1.deplacements possibles d'une piece.\n2.pieces adverse attaquables ou non.\n3.pieces pouvant se deplacer.\n4.les pieces adverses pouvant attaquer une piece" << endl;
    cout << endl;
}

void mask_choices(square *T, int *T2, turn camp)
{
    mask_choices_menu();
    cout << "choisissez le numero de masque de votre choix : ";
    int n;
    cin >> n;
    char choix;
    while (n < 1 || n > 4)
    {
        cout << "numero incorrect !\nVous voulez reessayez? (o/n) : ";
        cin >> choix;
        if (choix == 'o')
        {
            cout << "choisissez le numero de masque de votre choix : ";
            cin >> n;
        }
        if (choix == 'n')
            return;
    }
    if (n == 1)
    {
        cout << "Choisissez la case (ex: a1,e2,...) : ";
        string cas;
        cin >> cas;
        while (cas[0] < 'a' || cas[0] > 'h' || cas[1] - '0' < 1 || cas[1] - '0' > 8) // cas[i]-'0' donne la valeur de l'entier
        {
            cout << "Erreur! saisie incorrect. Voulez vous continuer? (o/n) : ";
            cin >> choix;
            if (choix == 'o')
            {
                cout << "Choisissez la case (ex: a1,e2,...) : ";
                cin >> cas;
            }
            else
            {
                return;
            }
        }
        pos p;
        p.lig = (cas[1] - '0') - 1;
        p.col = cas[0] - 'a';
        possible_move(T, T2, p);
        print_board(T, T2);
    }
    if (n == 2)
    {
        if (camp == blanc)
            highlight_attacked_pieces(T, T2, blanc);
        else
            highlight_attacked_pieces(T, T2, noir);
        print_board(T, T2);
    }
    if (n == 3)
    {
        if (camp == blanc)
            highlight_movable_pieces(T, T2, blanc);
        else
            highlight_movable_pieces(T, T2, noir);
        print_board(T, T2);
    }
    if (n == 4)
    {
        cout << "Choisissez la case (ex: a1,e2,...) : ";
        string cas;
        cin >> cas;
        while (cas[0] < 'a' || cas[0] > 'h' || cas[1] - '0' < 1 || cas[1] - '0' > 8)
        {
            cout << "Erreur! saisie incorrect. Voulez vous continuer? (o/n) : ";
            cin >> choix;
            if (choix == 'o')
            {
                cout << "Choisissez la case (ex: a1,e2,...) : ";
                cin >> cas;
            }
            else
            {
                return;
            }
        }
        pos p;
        p.lig = (cas[1] - '0') - 1;
        p.col = cas[0] - 'a';
        highlight_take_pieces(T, T2, p);
        print_board(T, T2);
    }
    cout << "Voulez-vous continuer? (o/n) : ";
    cin >> choix;
    if (choix == 'o')
        mask_choices(T, T2, camp);
    else
        return;
}