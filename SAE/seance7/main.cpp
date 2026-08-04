#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
using namespace std;
#include "game.hpp"
#include <ctime>
#include <fstream>

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    srand(time(NULL));                     // je l'ai pris sur google vu que le rand() ne donnait pas le vrai aleatoire.
                                           // avec srand les rand() utilises seront de vrai aleatoires.
    ofstream file("FEN1.txt", ios::trunc); // pour vider completement le fichier d'historique
    Game G;
    G.camp = blanc;
    cout << "voulez-vous affronter un autre joueur ou l'IA? \n taper 'a' pour affronter un joueur et 'b' pour affronter l'IA ";
    char choix, choix2;
    cin >> choix;
    while (choix != 'a' && choix != 'b')
    {
        cout << "voulez-vous affronter un autre joueur ou l'IA? \n taper 'a' pour affronter un joueur et 'b' pour affronter l'IA ";
        cin >> choix;
    }
    if (choix == 'a')
        G.parti = HumainHumain;
    else
        G.parti = HumainMachine;
    G.joueur = humain;
    G.N = 0; // le compteur des 50 coups
    G.gagnant = rien;
    G.roiblancbouge = false;
    G.roinoirbouge = false;
    G.tourblancdroitebouge = false;
    G.tourblancgauchebouge = false;
    G.tournoirdroitebouge = false;
    G.tournoirgauchebouge = false;
    G.T = empty();
    G.T2 = empty_mask();
    clear_mask(G.T2);
    start(G.T);
    print_board(G.T);
    while (G.N < 50 && G.gagnant == rien)
    {
        if (G.joueur == humain)
        {
            cout << "voulez-vous abandonner ? (o/n) : ";
            cin >> choix2;
            while (choix2 != 'o' && choix2 != 'n')
            {
                cout << "voulez-vous abandonner ? (o/n) : ";
                cin >> choix2;
            }

            if (choix2 == 'o' && G.camp == blanc)
                G.gagnant = noir;
            if (choix2 == 'o' && G.camp == noir)
                G.gagnant = blanc;
        }
        if (G.joueur == humain)
        {
            play_historique(&G);
            backtrack_historique(&G);
        }
        one_run(&G);
        G.N++;
    }
    if (G.N == 50 && G.gagnant == rien)
    {
        int scoreBlanc = 0, scoreNoir = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (estNoir(G.T, i, j))
                {
                    if (G.T[i * 8 + j] == P_noir)
                        scoreNoir++;
                    if (G.T[i * 8 + j] == N_noir || G.T[i * 8 + j] == B_noir)
                        scoreNoir += 3;
                    if (G.T[i * 8 + j] == R_noir)
                        scoreNoir += 5;
                    if (G.T[i * 8 + j] == Q_noir)
                        scoreNoir += 9;
                }
                else
                {
                    if (G.T[i * 8 + j] == P_blanc)
                        scoreBlanc++;
                    if (G.T[i * 8 + j] == N_blanc || G.T[i * 8 + j] == B_blanc)
                        scoreBlanc += 3;
                    if (G.T[i * 8 + j] == R_blanc)
                        scoreBlanc += 5;
                    if (G.T[i * 8 + j] == Q_blanc)
                        scoreBlanc += 9;
                }
        if (scoreBlanc > scoreNoir)
            G.gagnant = blanc;
        else if (scoreBlanc < scoreNoir)
            G.gagnant = noir;
        else
            G.gagnant = egalite;
    }
    if (G.gagnant == blanc)
        cout << "Victoire des Blancs!" << endl;
    if (G.gagnant == noir)
        cout << "Victoire des noirs!" << endl;
    if (G.gagnant == egalite)
        cout << "Match null !!" << endl;

    delete[] G.T;
    delete[] G.T2;
    return 0;
}
