#include "utilitaires.c"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

/*
 void *lire_clavier(void *arg){
    data_t * data = (data_t *)arg;

    char c;

    while(data->player->alive && !game_fini(*data->bomber) ) {
        if (_kbhit()) {
            // pthread_mutex_lock(&dmutex);
            c = _getch();
               if (c == ' ')
            {   pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 4;
                pthread_mutex_unlock(&dmutex);
                data->player->nb_bombe++;

            }

             else if (c==72&& data->bomber->plateau[data->player->posl-1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                            pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}

                data->player->posl =data->player->posl-1;
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 2;
                pthread_mutex_unlock(&dmutex);

            }
            else if (c == 80&& data->bomber->plateau[data->player->posl+1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){

                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 data->player->posl = data->player->posl+1;
                pthread_mutex_lock(&dmutex);
                         data->bomber->plateau[data->player->posl][data->player->posc]= 2;
                pthread_mutex_unlock(&dmutex);

            }

            else if ( c == 77 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 4 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 5) {
                if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                        pthread_mutex_lock(&dmutex);
                    data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}
                if (data->player->posc+1== 33)
                {
                    data->player->posc = 0;

            }
                else {
                data->player->posc = data->player->posc+1;

            }
            pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player->posl][data->player->posc]= 2;
            pthread_mutex_unlock(&dmutex);
            }

            else if (c == 75&& data->bomber->plateau[data->player->posl][data->player->posc-1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 4 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 5) {
            if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 if (data->player->posc-1== -1)
                {
                    data->player->posc = 32;
                }
                else {
                data->player->posc = data->player->posc-1;
                }
                pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player->posl][data->player->posc]= 2;
                pthread_mutex_unlock(&dmutex);
            }



        }
       // pthread_mutex_unlock(&dmutex);
    //Sleep(50);
    }
 }

  void *lire_clavier2(void *arg){
    data_t * data = (data_t *)arg;

    char c;

    while(data->player->alive && !game_fini(*data->bomber) ) {
        if (_kbhit()) {
       // pthread_mutex_lock(&dmutex);
            c = _getch();
               if (c == 'w')
            {   pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 6;
                pthread_mutex_unlock(&dmutex);
                data->player->nb_bombe++;

            }

             else if (c=='z'&& data->bomber->plateau[data->player->posl-1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                data->player->posl =data->player->posl-1;
                pthread_mutex_lock(&dmutex);
                        data->bomber->plateau[data->player->posl][data->player->posc]= 5;
                pthread_mutex_unlock(&dmutex);

            }
            else if (c == 's'&& data->bomber->plateau[data->player->posl+1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}
                data->player->posl = data->player->posl+1;
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 5;
                pthread_mutex_unlock(&dmutex);

            }

            else if ( c == 'd' && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 6 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 2 ) {
                if (data->bomber->plateau[data->player->posl][data->player->posc]!= 6){
                        pthread_mutex_lock(&dmutex);
                    data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}
                if (data->player->posc+1== 33)
                {
                    data->player->posc = 0;

                }
                else {
                data->player->posc = data->player->posc+1;

                }
                pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player->posl][data->player->posc]= 5;
            pthread_mutex_unlock(&dmutex);
            }

            else if (c == 'q'&& data->bomber->plateau[data->player->posl][data->player->posc-1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 6 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 2) {
            if (data->bomber->plateau[data->player->posl][data->player->posc]!= 6){
                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 if (data->player->posc-1== -1)
                {
                    data->player->posc = 32;
}
                else {
                data->player->posc = data->player->posc-1;
}           pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player->posl][data->player->posc]= 5;
            pthread_mutex_unlock(&dmutex);
            }



        }
        // pthread_mutex_unlock(&dmutex);
        //Sleep(50);
    }
 }

*/


void *lire_clavier(void *arg){
    data_score * data = (data_score *)arg;

    char c;

    while(data->player->alive && data->player2->alive&& !game_fini(*data->bomber) ) {
        if (_kbhit()) {
            // pthread_mutex_lock(&dmutex);
            c = _getch();
               if (c == ' ')
            {   pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 4;
                pthread_mutex_unlock(&dmutex);
                data->player->nb_bombe++;

            }

             else if (c==72&& data->bomber->plateau[data->player->posl-1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                            pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}

                data->player->posl =data->player->posl-1;
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 2;
                pthread_mutex_unlock(&dmutex);

            }
            else if (c == 80&& data->bomber->plateau[data->player->posl+1][data->player->posc]== 0) {
                    if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){

                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 data->player->posl = data->player->posl+1;
                pthread_mutex_lock(&dmutex);
                         data->bomber->plateau[data->player->posl][data->player->posc]= 2;
                pthread_mutex_unlock(&dmutex);

            }

            else if ( c == 77 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 4 && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 5
                     && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 6) {
                if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                        pthread_mutex_lock(&dmutex);
                    data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}
                if (data->player->posc+1== 33)
                {
                    data->player->posc = 0;

            }
                else {
                data->player->posc = data->player->posc+1;

            }
            pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player->posl][data->player->posc]= 2;
            pthread_mutex_unlock(&dmutex);
            }

            else if (c == 75&& data->bomber->plateau[data->player->posl][data->player->posc-1]!= 1 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 3
                     && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 4 && data->bomber->plateau[data->player->posl][data->player->posc-1]!= 5
                     && data->bomber->plateau[data->player->posl][data->player->posc+1]!= 6) {
            if (data->bomber->plateau[data->player->posl][data->player->posc]!= 4){
                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player->posl][data->player->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 if (data->player->posc-1== -1)
                {
                    data->player->posc = 32;
                }
                else {
                data->player->posc = data->player->posc-1;
                }
                pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player->posl][data->player->posc]= 2;
                pthread_mutex_unlock(&dmutex);
            }
            else if (c == 'w')
            {   pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 6;
                pthread_mutex_unlock(&dmutex);
                data->player2->nb_bombe++;

            }

             else if (c=='z'&& data->bomber->plateau[data->player2->posl-1][data->player2->posc]== 0) {
                    if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 4){
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                data->player2->posl =data->player2->posl-1;
                pthread_mutex_lock(&dmutex);
                        data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
                pthread_mutex_unlock(&dmutex);

            }
            else if (c == 's'&& data->bomber->plateau[data->player2->posl+1][data->player2->posc]== 0) {
                    if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 4){
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                pthread_mutex_unlock(&dmutex);}
                data->player2->posl = data->player2->posl+1;
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
                pthread_mutex_unlock(&dmutex);

            }

            else if ( c == 'd' && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 1 && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 3
                     && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 6 && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 2
                     && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 4) {
                if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 6){
                        pthread_mutex_lock(&dmutex);
                    data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}
                if (data->player2->posc+1== 33)
                {
                    data->player2->posc = 0;

                }
                else {
                data->player2->posc = data->player2->posc+1;

                }
                pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
            pthread_mutex_unlock(&dmutex);
            }

            else if (c == 'q'&& data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 1 && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 3
                     && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 6 && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 2
                     && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 4) {
            if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 6){
                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 if (data->player2->posc-1== -1)
                {
                    data->player2->posc = 32;
}
                else {
                data->player2->posc = data->player2->posc-1;
}           pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
            pthread_mutex_unlock(&dmutex);
            }


        }
       // pthread_mutex_unlock(&dmutex);
    Sleep(50);
    }
 }

void *deplacer_bomber(void *arg) {

    data_score * data = (data_score *)arg;


    while(data->player->alive && !game_fini(*data->bomber) && data->player2->alive) {
        //pthread_mutex_lock(&dmutex);


        afficher_plateau(*data->bomber,*data->player,*data->player2);

        //pthread_mutex_unlock(&dmutex);

        Sleep(50);
    }
}
void *explo(void *arg) {

    data_t * data = (data_t *)arg;
    while (data->player->alive && !game_fini(*data->bomber)){
    expo_bombe(data->bomber,data->player,2);
Sleep(100);
    }
}

void *explo2(void *arg) {

    data_t * data = (data_t *)arg;
    while (data->player->alive && !game_fini(*data->bomber)){
    expo_bombe2(data->bomber,data->player,2);
Sleep(100);
    }
}


int main() {
    data_t data;
    data_t data2;
    data_score datas;
    bomber_t bomber;
    player_t player;
    player_t player2;

    data.bomber=&bomber;
    data.player=&player;

    data2.bomber=&bomber;
    data2.player=&player2;

    datas.bomber=&bomber;
    datas.player=&player;
    datas.player2=&player2;
    time_t now;
    time(&now);
    pthread_t anim,clavier,bombe,bombe2,clavier2;
    srand(time(0));

    player.alive=1;
    player.score=0;
    player.nb_bombe=0;

    player2.alive=1;
    player2.score=0;
    player2.nb_bombe=0;
	lire_plateau("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\plateau.txt",&bomber);

    placer_bomber(&bomber,&player,1);
    placer_bomber(&bomber,&player2,2);
    placer_obstacles(&bomber);

    pthread_create(&anim,NULL,deplacer_bomber,&datas);
   /*pthread_create(&clavier,NULL,lire_clavier,&data);

    pthread_create(&clavier2,NULL,lire_clavier2,&data2);*/


    pthread_create(&clavier,NULL,lire_clavier,&datas);
    pthread_create(&bombe,NULL,explo,&data);
    pthread_create(&bombe2,NULL,explo2,&data2);
    //pthread_join(clavier,NULL);
    pthread_join(anim,NULL);

    //pthread_join(anim,NULL);

    printf("donnez votre joueur 1 \n");
    scanf("%s",&player2.nom);
    printf("donnez votre joueur 2 \n");
    scanf("%s",&player.nom);

    if (player.alive==1 && player2.alive==1){
        if (player.score>player2.score)
            printf("%s a gagné par le score de %.2f",player.nom,((float)player.score/(float)player.nb_bombe));
        else
            printf("%s a gagné par le score de %.2f",player2.nom,((float)player2.score/(float)player2.nb_bombe));
    }
    else if (player.alive == 0)
        printf("%s a gagné par le score de %.2f",player.nom,((float)player.score/(float)player.nb_bombe));
    else
        printf("%s a gagné par le score de %.2f",player2.nom,((float)player2.score/(float)player2.nb_bombe));

    //printf("score de : %.2f par %s le %s",((float)player.score/(float)player.nb_bombe),player.nom,  ctime(&now));
    //enregistrer("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\score.txt",bomber);
	return 0;

	//il ya bug dans le score
}
