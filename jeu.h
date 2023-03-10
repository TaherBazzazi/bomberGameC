#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <windows.h>
#include <conio.h>
// Mettez en commentaire cette ligne si vous êtes sous Windows :
//#include <termios.h>


#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data
#define SERVER "127.0.0.1"	//ip address of udp server

// Mettez en commentaire cette ligne si vous êtes sous Windows :
//static struct termios origtc, newtc;

//enum directions {HAUT,BAS,GAUCHE,DROITE};
typedef struct{
    int posl; // ligne actuelle de l'étoile
    int posc; // colonne actuelle de l'étoile
    int score;
    int nb_bombe;
    char nom[50];
    int alive;
} player_t;


typedef struct{
    int **plateau;
    int lignes; // Nombre de lignes de plateau
    int colonnes; // Nobre de colonnes de plateau
} bomber_t;

typedef struct data {
    bomber_t *bomber;
    player_t *player;
}data_t;

typedef struct data_s {
    bomber_t *bomber;
    player_t *player;
    player_t *player2;
}data_score;

typedef struct data_send {
    bomber_t *bomber;
    player_t *player;
    player_t *player2;
    SOCKET *s;
}data_send_t;

typedef struct data_rec {
    bomber_t *bomber;
    player_t *player;
    player_t *player2;
    int *s;


}data_rec_t;



void * lire_clavier(void *arg);
void lire_plateau(char *fichier,bomber_t *bomber);
void clearScreen();
void afficher_plateau(bomber_t bomber,player_t player,player_t player2);
//void placer_bomber(bomber_t *bomber);
void placer_bomber(bomber_t *bomber,player_t *player,int n);
void expo_bombe(bomber_t *bomber,player_t *player,player_t *player2,int n);
void afficher_plateau_client(bomber_t bomber,player_t player,player_t player2);
int game_fini(bomber_t bomber);
void enregistrer(char *fichier,bomber_t bomber);
void *explo(void *arg) ;
void expo_bombe2(bomber_t *bomber,player_t *player,player_t *player2,int n);
