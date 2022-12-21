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
void afficher_plateau(bomber_t bomber) {
	int i,j;
    system("cls");
	for (i=0;i<bomber.lignes;i++){
        for (j=0;j<bomber.colonnes;j++){
            if(bomber.plateau[i][j] == 0)
                printf(" ");
            else if(bomber.plateau[i][j] == 1)
                printf("#");
            else if(bomber.plateau[i][j] == 2)
                printf("B");
            else if(bomber.plateau[i][j] == 3)
                printf("X");

        }
        printf("\n");
	}
}

/*
 * Placer l'étoile dans une case choisie aléatoirement
 * en évitant les ases obstacles.
 */

void placer_bomber(bomber_t *bomber) {
    int c,l;
    do{
        c=(int)(rand()% bomber->colonnes);
        l=(int)(rand()% bomber->lignes);
    }while(bomber->plateau[l][c] == 1);
    bomber->posc=c;
    bomber->posl=l;
    bomber->plateau[l][c]=2;


}
