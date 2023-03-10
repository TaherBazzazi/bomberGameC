#include "jeu.h"
/*
 * Lire le plateau du jeu depuis un fichier et remplir la structure star
 */
void lire_plateau(char *fichier,bomber_t *bomber) {
	FILE *f;
	char str[100];
	int i,j;
	char ch;
    bomber->lignes = 0;
	f = fopen(fichier,"r");
    if (f == NULL){
        printf("Je ne peux pas ouvrir le fichier %s\n",fichier);
        exit(-1);
    }
	while (fgets(str,sizeof(str),f) != NULL){
		str[strlen(str)-1] = '\0';
		bomber->colonnes = strlen(str);
		bomber->lignes++;
	}
	fclose(f);
	bomber->plateau = (int **)malloc(bomber->lignes*sizeof(int *));
	for (i=0; i < bomber->lignes;i++){
		bomber->plateau[i] = (int *)malloc(bomber->colonnes*sizeof(int));
	}
	f = fopen(fichier,"r");
	i = 0; j = 0;
	while ((ch = getc(f)) != EOF) {
        if (ch != '\n') {
            if (ch == '#') {
                bomber->plateau[i][j] = 1;
            }else{
                bomber->plateau[i][j] = 0;
            }
            j++;
            if (j == bomber->colonnes) {
                j = 0;
                i++;
            }
        }
	}
}
/*
 * Effacer le contenu de l'écran en mode terminal
 * Check this for more details : http://www.cplusplus.com/articles/4z18T05o/
 */
void clearScreen()
{
    int n;
    for (n = 0; n < 10; n++)
        printf( "\n\n\n\n\n\n\n\n\n\n" );
}
/*
 * Afficher le plateau sur l'écran en remplaçant 1 par '#'
 * 0 par ' ' et 2 par '*'
 */
void afficher_plateau(bomber_t bomber,player_t player,player_t player2) {
	int i,j;
    system("cls");

    //printf("cords %d ; %d ;nb_obs %d ;nb_bomb %d ;alive %d ;jeu_fini %d \n",player.posl,player.posc, player.score,player.nb_bombe,player.alive, game_fini(bomber));
	printf("joueur1 nb bombe: %d joueur1 score: %d\n",player.nb_bombe,player.score);
	printf("joueur2 nb bombe: %d joueur2 score: %d\n",player2.nb_bombe,player2.score);
	for (i=0;i<bomber.lignes;i++){
        for (j=0;j<bomber.colonnes;j++){
            if(bomber.plateau[i][j] == 0)
                printf(" ");
            else if(bomber.plateau[i][j] == 6)
                printf("o");
            else if(bomber.plateau[i][j] == 1)
                printf("#");
            else if(bomber.plateau[i][j] == 4)
                printf("O");
            else if(bomber.plateau[i][j] == 2)
                printf("B");
            else if(bomber.plateau[i][j] == 3)
                printf("X");
            else if(bomber.plateau[i][j] == 5)
                printf("P");


        }
        printf("\n");
	}
}
void afficher_plateau_client(bomber_t bomber,player_t player,player_t player2) {
	int i,j;
    system("cls");
    printf("joueur1 nb bombe: %d joueur1 score: %d\n",player.nb_bombe,player.score);
	printf("joueur2 nb bombe: %d joueur2 score: %d\n",player2.nb_bombe,player2.score);
	for (i=0;i<bomber.lignes;i++){
        for (j=0;j<bomber.colonnes;j++){
            if(bomber.plateau[i][j] == 0)
                printf(" ");
            else if(bomber.plateau[i][j] == 6)
                printf("o");
            else if(bomber.plateau[i][j] == 1)
                printf("#");
            else if(bomber.plateau[i][j] == 4)
                printf("O");
            else if(bomber.plateau[i][j] == 2)
                printf("B");
            else if(bomber.plateau[i][j] == 3)
                printf("X");
            else if(bomber.plateau[i][j] == 5)
                printf("P");
            else
                printf("s");

        }
        printf("\n");
	}
}

/*
 * Placer l'étoile dans une case choisie aléatoirement
 * en évitant les ases obstacles.
 */
void placer_obstacles(bomber_t *bomber) {
for (int i=0;i < 20;i++){
int c,l;
    do{
        c=(int)(1+(rand()%(bomber->colonnes-2)));
        l=(int)(1+(rand()%(bomber->lignes-2)));
    }while( bomber->plateau[l][c] == 1);

    bomber->plateau[l][c]=3;}
}

void placer_bomber(bomber_t *bomber,player_t *player,int n) {
    int c,l;
    do{
        c=(int)(rand()% bomber->colonnes);
        l=(int)(rand()% bomber->lignes);
    }while(bomber->plateau[l][c] != 0);
    player->posc=c;
    player->posl=l;
    if ( n==1)
    bomber->plateau[player->posl][player->posc]=2;
    if ( n==2)
    bomber->plateau[player->posl][player->posc]=5;

}

void expo_bombe(bomber_t *bomber,player_t *player,player_t *player2,int n){
    int i,j;
    for (i=0;i<bomber->lignes;i++){
        for (j=0;j<bomber->colonnes;j++){
            if(bomber->plateau[i][j] == 4 ){
                sleep(n);

            for (int k=0; k<n+1;k++){
                if(i+k<bomber->lignes  ){
            if(bomber->plateau[i+k][j] != 1 &&bomber->plateau[i+1][j] != 1 ){

            if(bomber->plateau[i+k][j] == 3 )
                player->score++;
            if(bomber->plateau[i+k][j] == 2 )
                player->alive=0;
            if(bomber->plateau[i+k][j] == 5 )
                player2->alive=0;

             bomber->plateau[i+k][j]=0;}
             }

            if(i-k>0 ){
            if (bomber->plateau[i-k][j] != 1 &&bomber->plateau[i-1][j] != 1 ){
            if( bomber->plateau[i-k][j] == 3)
                player->score++;
            if( bomber->plateau[i-k][j] == 2)
                player->alive=0;
            if(bomber->plateau[i-k][j] == 5 )
                player2->alive=0;

                bomber->plateau[i-k][j]=0;}
                }

            }

            for (int k=0; k<n+1;k++){
                if(j+k<bomber->colonnes  ){
            if(bomber->plateau[i][j+k] != 1 && bomber->plateau[i][j+1] != 1)
                {
                if(bomber->plateau[i][j+k] == 3)
                   player->score++;
                if(bomber->plateau[i][j+k] == 2)
                   player->alive=0;
                if(bomber->plateau[i][j+k] == 5)
                    player2->alive=0;
                   bomber->plateau[i][j+k]=0;
                }
                }

                if (j-k>0){
                if ( bomber->plateau[i][j-k] != 1 && bomber->plateau[i][j-1] != 1 ){
                 if(bomber->plateau[i][j-k] == 3)
                   player->score++;
                if(bomber->plateau[i][j-k] == 2)
                    player->alive=0;
                if(bomber->plateau[i][j-k] == 5 )
                    player2->alive=0;
                bomber->plateau[i][j-k]=0;
                }}
            }
} }}}

void expo_bombe2(bomber_t *bomber,player_t *player,player_t *player2,int n){
    int i,j;
    for (i=0;i<bomber->lignes;i++){
        for (j=0;j<bomber->colonnes;j++){
            if(bomber->plateau[i][j] == 6 ){
                sleep(n);

            for (int k=0; k<n+1;k++){
                if(i+k<bomber->lignes  ){
            if(bomber->plateau[i+k][j] != 1 &&bomber->plateau[i+1][j] != 1 ){

            if(bomber->plateau[i+k][j] == 3 )
                player->score++;
            if(bomber->plateau[i+k][j] == 5 )
                player->alive=0;
            if(bomber->plateau[i+k][j] == 2 )
                player2->alive=0;

             bomber->plateau[i+k][j]=0;}}

            if(i-k>0 ){
            if (bomber->plateau[i-k][j] != 1 &&bomber->plateau[i-1][j] != 1 ){
            if( bomber->plateau[i-k][j] == 3)
                player->score++;
            if( bomber->plateau[i-k][j] == 5)
                player->alive=0;
            if(bomber->plateau[i-k][j] == 2 )
                player2->alive=0;

                bomber->plateau[i-k][j]=0;}
                }

            }

            for (int k=0; k<n+1;k++){
                if(j+k<bomber->colonnes  ){
            if(bomber->plateau[i][j+k] != 1 && bomber->plateau[i][j+1] != 1)
                {
                if(bomber->plateau[i][j+k] == 3)
                   player->score++;
                if(bomber->plateau[i][j+k] == 5)
                   player->alive=0;
                if(bomber->plateau[i][j+k] == 2 )
                player2->alive=0;

                   bomber->plateau[i][j+k]=0;
                }}

                if (j-k>0){
                if ( bomber->plateau[i][j-k] != 1 && bomber->plateau[i][j-1] != 1 ){
                 if(bomber->plateau[i][j-k] == 3)
                   player->score++;
                if(bomber->plateau[i][j-k] == 5)
                    player->alive=0;
                if(bomber->plateau[i][j-k] == 2 )
                player2->alive=0;

                bomber->plateau[i][j-k]=0;
                }}
            }
} }}}


int game_fini(bomber_t bomber){
int i,j;
    for (i=0;i<bomber.lignes;i++){
        for (j=0;j<bomber.colonnes;j++){
            if(bomber.plateau[i][j] == 3 ){
               return 0;
            }}}
return 1;
}


/*void enregistrer(char *fichier,bomber_t bomber){
    time_t now;
    time(&now);
    FILE *f;
    f = fopen(fichier,"a");
    if (f == NULL){
        printf("Je ne peux pas ouvrir le fichier d'enregistrement %s\n",fichier);
        exit(-1);
    }

    fprintf(f,"score de : %.2f par %s le %s",((float)bomber.score/(float)bomber.nb_bombe),bomber.nom,  ctime(&now));

    fclose(f);

}*/


