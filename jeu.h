#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <windows.h>
#include <conio.h>
// Mettez en commentaire cette ligne si vous êtes sous Windows :
//#include <termios.h>
#include <windows.h>
#include <conio.h>


// Mettez en commentaire cette ligne si vous êtes sous Windows :
//static struct termios origtc, newtc;

//enum directions {HAUT,BAS,GAUCHE,DROITE};

typedef struct{
    int **plateau;
    int lignes; // Nombre de lignes de plateau
    int colonnes; // Nobre de colonnes de plateau
    int posl; // ligne actuelle de l'étoile
    int pl; // ligne précédente de l'étoile
    int posc; // colonne actuelle de l'étoile
    int pc; // colonne précédente de l'étoile
    int alive;
    int score;
    int nb_bombe;
    char nom[50];
} bomber_t;

void * lire_clavier(void *arg);
void lire_plateau(char *fichier,bomber_t *bomber);
void clearScreen();
void afficher_plateau(bomber_t bomber);
void placer_bomber(bomber_t *bomber);
void expo_bombe(bomber_t *bomber,int n);
int game_fini(bomber_t bomber);
void enregistrer(char *fichier,bomber_t bomber);
