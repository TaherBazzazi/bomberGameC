#include "utilitaires.c"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;


 void *lire_clavier(void *arg){
    data_t * data = (data_t *)arg;

    printf("%d ; %d ; %d ; %d ; %d \n",data->player->posl,data->player->posc,data->player->score,data->player->alive, game_fini(*data->bomber));
    char c;
    while(data->player->alive && !game_fini(*data->bomber) ) {
        if (_kbhit()) {
            c = _getch();
               if (c == ' ')
            {    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 4;
                data->player->nb_bombe++;

            }

             else if (c==72&& data->bomber->plateau[data->player->posl-1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4)
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                data->player->posl =data->player->posl-1;
                        data->bomber->plateau[data->player->posl][data->player->posc]= 2;

            }
            else if (c == 80&& data->bomber->plateau[data->player->posl+1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4)
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                 data->player->posl = data->player->posl+1;
                         data->bomber->plateau[data->player->posl][data->player->posc]= 2;

            }

            else if ( c == 77 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 4) {
                if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4)
                    data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                if (data->player->posc+1== 33)
                {
                    data->player->posc = 0;

}
                else {
                data->player->posc = data->player->posc+1;

}
            data->bomber->plateau[data->player->posl][data->player->posc]= 2;
            }

            else if (c == 75&& data->bomber->plateau[data->player->posl][data->player->posc-1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 4) {
            if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4)
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;

                 if (data->player->posc-1== -1)
                {
                    data->player->posc = 32;
}
                else {
                data->player->posc = data->player->posc-1;
}
            data->bomber->plateau[data->player->posl][data->player->posc]= 2;
            }


            pthread_mutex_unlock(&dmutex);
        }

        Sleep(50);
    }
 }




void *deplacer_bomber(void *arg) {

    data_t * data = (data_t *)arg;


    while(data->player->alive && !game_fini(*data->bomber)) {
        //pthread_mutex_lock(&dmutex);


        afficher_plateau(*data->bomber,*data->player);

        //pthread_mutex_unlock(&dmutex);

        Sleep(100);
    }
}
void *explo(void *arg) {

    data_t * data = (data_t *)arg;


    //printf("%d ; %d ; %d ; %d ; %d \n",player->posl,player->posc, player->score, player->alive, game_fini(*bomber));
    while (data->player->alive && !game_fini(*data->bomber)){
    expo_bombe(data->bomber,data->player,2);
Sleep(100);
    }
}

int main() {
    data_t data;
    bomber_t bomber;
    player_t player;
    data.bomber=&bomber;
    data.player=&player;

    time_t now;
    time(&now);
    pthread_t anim,clavier,bombe;
    srand(time(0));

    player.alive=1;
    player.score=0;
    player.nb_bombe=0;

	lire_plateau("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\plateau.txt",&bomber);

    placer_bomber(&bomber,&player,1);
    placer_bomber(&bomber,&player,2);
    placer_obstacles(&bomber);

    pthread_create(&anim,NULL,deplacer_bomber,&data);
    pthread_create(&clavier,NULL,lire_clavier,&data);
    pthread_create(&bombe,NULL,explo,&data);
    pthread_join(anim,NULL);

    printf("donnez votre nom \n");
    scanf("%s",&player.nom);
    printf("score de : %.2f par %s le %s",((float)player.score/(float)player.nb_bombe),player.nom,  ctime(&now));
    //enregistrer("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\score.txt",bomber);
	return 0;

	//il ya bug dans le score
}
