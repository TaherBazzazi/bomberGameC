#include "utilitaires.c"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;


 void *lire_clavier(void *arg){
    bomber_t * bomber = (bomber_t *)arg;
    char c;
    while(1) {
        if (_kbhit()) {
            c = _getch();
            pthread_mutex_lock(&dmutex);
            if (c=='z'&& bomber->plateau[bomber->posl-1][bomber->posc]== 0) {
                bomber->plateau[bomber->posl][bomber->posc]= 0;
                bomber->posl = bomber->posl-1;
            }
            else if (c == 's'&& bomber->plateau[bomber->posl+1][bomber->posc]== 0) {
                bomber->plateau[bomber->posl][bomber->posc]= 0;
                 bomber->posl = bomber->posl+1;
            }

            else if (c == 'd'&& bomber->plateau[bomber->posl][bomber->posc+1]== 0 ) {
                if (bomber->posc+1== 33)
                {bomber->plateau[bomber->posl][bomber->posc]= 0;
                    bomber->posc = 0;}
                else {bomber->plateau[bomber->posl][bomber->posc]= 0;
                bomber->posc = bomber->posc+1;}
            }
            else if (c == 'q'&& bomber->plateau[bomber->posl][bomber->posc-1]== 0) {
                 if (bomber->posc-1== -1)
                {bomber->plateau[bomber->posl][bomber->posc]= 0;
                    bomber->posc = 32;}
                else {bomber->plateau[bomber->posl][bomber->posc]= 0;
                bomber->posc = bomber->posc-1;}
            }

            else if (c == ' ')
            {
                bomber->plateau[bomber->posl][bomber->posc]= 4;
            }

            pthread_mutex_unlock(&dmutex);
        }
        Sleep(50);
    }
 }




void *deplacer_bomber(void *arg) {
    bomber_t * bomber = (bomber_t *)arg;

    while(1) {
        pthread_mutex_lock(&dmutex);

        bomber->plateau[bomber->posl][bomber->posc]= 2;

        afficher_plateau(*bomber);
        pthread_mutex_unlock(&dmutex);

        Sleep(100);
    }
}

int main() {
    bomber_t bomber;

 pthread_t anim,clavier;
    srand(time(0));


	lire_plateau("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\plateau.txt",&bomber);
	//placer_obstacles(&bomber);
    placer_bomber(&bomber);
    //placer_obstacles(&bomber);

    //afficher_plateau(star);
    pthread_create(&anim,NULL,deplacer_bomber,&bomber);
    pthread_create(&clavier,NULL,lire_clavier,&bomber);
    pthread_join(anim,NULL);
	return 0;
}
