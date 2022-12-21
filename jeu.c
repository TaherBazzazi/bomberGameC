#include "utilitaires.c"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;


 void *lire_clavier(void *arg){
    star_t * star = (star_t *)arg;
    char c;
    while(1) {
        if (_kbhit()) {
            c = _getch();
            pthread_mutex_lock(&dmutex);
            if (c=='z') {
                star->direction = HAUT;
            }else if (c == 's') {
                star->direction = BAS;
            }else if (c == 'd') {
                star->direction = DROITE;
            }else if (c == 'q') {
                star->direction = GAUCHE;
            }
            pthread_mutex_unlock(&dmutex);
        }
        Sleep(1000);
    }
 }



void calculer_direction(star_t *star) {
    int i,j,l,c;
        for (l=0; l<star->lignes; l++){
            for (c=0; c<star->colonnes; c++){
                if(star->plateau[l][c] == 2){
                    i=l;
                    j=c;
                }
            }
        }

    if (star->direction== GAUCHE && star->plateau[i][j-1]== 1){
            star->direction=BAS;
    }
    if (star->direction== BAS && star->plateau[i+1][j]==1){
            star->direction=DROITE;
    }
    if (star->direction== DROITE && star->plateau[i][j+1]==1){
            star->direction=HAUT;
    }
    if (star->direction== HAUT && star->plateau[i-1][j]==1){
            star->direction=GAUCHE;
    }

}

void *deplacer_star(void *arg) {
    star_t * star = (star_t *)arg;

    while(1) {
        pthread_mutex_lock(&dmutex);

        calculer_direction(star);

        int i,j,l,c;
        for (l=0;l<star->lignes;l++){
            for (c=0;c<star->colonnes;c++){
                if(star->plateau[l][c] == 2){
                    i=l;
                    j=c;
                }
            }
        }


            if(star->direction == HAUT){
                star->plateau[i][j]=0;
                star->plateau[i-1][j]=2;
               // printf("changing %d  %d ",i,j);
               }

            else if(star->direction == BAS){
                star->plateau[i][j]=0;
                star->plateau[i+1][j]=2;
               // printf("changing1 %d  %d ",i,j);
            }

            else if(star->direction == GAUCHE){
                star->plateau[i][j]=0;
                star->plateau[i][j-1]=2;
                //printf("changing2  %d  %d  %d  %d ",i,j,star->plateau[i][j],star->plateau[i][j-1]);
            }

            else if(star->direction == DROITE){
                star->plateau[i][j]=0;
                star->plateau[i][j+1]=2;
                //printf("changing3 %d  %d ",i,j);
                }



        afficher_plateau(*star);
        pthread_mutex_unlock(&dmutex);
        // Sous windows utiliser Sleep(1000); en millisecondes
        Sleep(500);
    }
}

int main() {
    star_t star;
    star.direction = GAUCHE;
    pthread_t anim,clavier;
    srand(time(0));
	lire_plateau("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\plateau.txt",&star);
    placer_star(&star);
    //afficher_plateau(star);
    pthread_create(&anim,NULL,deplacer_star,&star);
    pthread_create(&clavier,NULL,lire_clavier,&star);
    pthread_join(anim,NULL);
	return 0;
}
