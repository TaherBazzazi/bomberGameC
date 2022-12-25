#include "utilitaires.c"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;


 void *lire_clavier(void *arg){
    bomber_t * bomber = (bomber_t *)arg;
    char c;
    while(bomber->alive && !game_fini(*bomber) ) {
        if (_kbhit()) {
            c = _getch();
               if (c == ' ')
            {    pthread_mutex_lock(&dmutex);
                bomber->plateau[bomber->posl][bomber->posc]= 4;
                bomber->nb_bombe++;

            }

             else if (c=='z'&& bomber->plateau[bomber->posl-1][bomber->posc]== 0) {
                    if (bomber->plateau[bomber->posl][bomber->posc]!= 4)
                bomber->plateau[bomber->posl][bomber->posc]= 0;
                bomber->posl = bomber->posl-1;
                        bomber->plateau[bomber->posl][bomber->posc]= 2;

            }
            else if (c == 's'&& bomber->plateau[bomber->posl+1][bomber->posc]== 0) {
                    if (bomber->plateau[bomber->posl][bomber->posc]!= 4)
                bomber->plateau[bomber->posl][bomber->posc]= 0;
                 bomber->posl = bomber->posl+1;
                         bomber->plateau[bomber->posl][bomber->posc]= 2;

            }

            else if (c == 'd'&& bomber->plateau[bomber->posl][bomber->posc+1]!= 1 && bomber->plateau[bomber->posl][bomber->posc+1]!= 3 && bomber->plateau[bomber->posl][bomber->posc+1]!= 4) {
                if (bomber->plateau[bomber->posl][bomber->posc]!= 4)
                    bomber->plateau[bomber->posl][bomber->posc]= 0;
                if (bomber->posc+1== 33)
                {
                    bomber->posc = 0;

}
                else {
                bomber->posc = bomber->posc+1;

}
            bomber->plateau[bomber->posl][bomber->posc]= 2;
            }

            else if (c == 'q'&& bomber->plateau[bomber->posl][bomber->posc-1]!= 1 && bomber->plateau[bomber->posl][bomber->posc-1]!= 3 && bomber->plateau[bomber->posl][bomber->posc-1]!= 4) {
            if (bomber->plateau[bomber->posl][bomber->posc]!= 4)
                bomber->plateau[bomber->posl][bomber->posc]= 0;

                 if (bomber->posc-1== -1)
                {
                    bomber->posc = 32;
}
                else {
                bomber->posc = bomber->posc-1;
}
            bomber->plateau[bomber->posl][bomber->posc]= 2;
            }


            pthread_mutex_unlock(&dmutex);
        }

        Sleep(50);
    }
 }




void *deplacer_bomber(void *arg) {
    bomber_t * bomber = (bomber_t *)arg;

    while(bomber->alive && !game_fini(*bomber)) {
        //pthread_mutex_lock(&dmutex);


        afficher_plateau(*bomber);

        //pthread_mutex_unlock(&dmutex);

        Sleep(100);
    }
}
void *explo(void *arg) {

     bomber_t * bomber = (bomber_t *)arg;
    while (bomber->alive && !game_fini(*bomber)){
expo_bombe(bomber,2);
Sleep(100);
    }
}

int main() {
    bomber_t bomber;
    time_t now;
    time(&now);
 pthread_t anim,clavier,bombe;
    srand(time(0));
    bomber.alive=1;
    bomber.score=0;
    bomber.nb_bombe=0;

	lire_plateau("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\plateau.txt",&bomber);
	//placer_obstacles(&bomber);
    placer_bomber(&bomber);
    placer_obstacles(&bomber);

    //afficher_plateau(bomber);

    pthread_create(&anim,NULL,deplacer_bomber,&bomber);
    pthread_create(&clavier,NULL,lire_clavier,&bomber);
    pthread_create(&bombe,NULL,explo,&bomber);
    pthread_join(anim,NULL);

    printf("donnez votre nom \n");
    scanf("%s",&bomber.nom);
    printf("score de : %.2f par %s le %s",(float)(bomber.score/bomber.nb_bombe),bomber.nom,  ctime(&now));
    enregistrer("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\score.txt",bomber);
	return 0;

	//il ya bug dans le score
}
