//#include "utilitaires.c"
#include "jeu.h"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;

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
                if (data->player->posc+1== 33&& data->bomber->plateau[data->player->posl][0]==0)
                {
                    data->player->posc = 0;

                }
                else if(data->player->posc+1== 33 && data->bomber->plateau[data->player->posl][0]!=0)
                    data->player->posc = 32;
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

                 if (data->player->posc-1== -1 && data->bomber->plateau[data->player->posl][32]==0)
                {
                    data->player->posc = 32;
                }
                else if(data->player->posc-1== -1 && data->bomber->plateau[data->player->posl][32]!=0)
                    data->player->posc = 0;
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
    data_send_t * data = (data_send_t *)arg;

    SOCKET s=data->s;
    int slen , recv_len;
	char buf[BUFLEN];
	struct sockaddr_in si_other;
	slen = sizeof(si_other) ;

        //printf("Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{

			exit(EXIT_FAILURE);
		}
		strcpy(data->player2->nom,buf);


		//now reply the client with the same data
		if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
		{

			exit(EXIT_FAILURE);
		}



    char c;
    while(data->player->alive && data->player2->alive&& !game_fini(*data->bomber) ) {
        memset(buf,'\0', BUFLEN);
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);

             if (buf[0] == 'w')
            {   pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 6;
                pthread_mutex_unlock(&dmutex);
                data->player2->nb_bombe++;

            }

             else if (buf[0]=='z'&& data->bomber->plateau[data->player2->posl-1][data->player2->posc]== 0) {
                    if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 6){
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                data->player2->posl =data->player2->posl-1;
                pthread_mutex_lock(&dmutex);
                        data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
                pthread_mutex_unlock(&dmutex);

            }
            else if (buf[0] == 's'&& data->bomber->plateau[data->player2->posl+1][data->player2->posc]== 0) {
                    if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 6){
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                pthread_mutex_unlock(&dmutex);}
                data->player2->posl = data->player2->posl+1;
                pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
                pthread_mutex_unlock(&dmutex);

            }

            else if ( buf[0] == 'd' && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 1 && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 3
                     && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 6 && data->bomber->plateau[data->player2->posl][data->player2->posc+1]!= 2
                     && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 4) {
                if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 6){
                        pthread_mutex_lock(&dmutex);
                    data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                    pthread_mutex_unlock(&dmutex);}
                if (data->player2->posc+1== 33 && data->bomber->plateau[data->player2->posl][0]==0)
                {
                    data->player2->posc = 0;
                }
                else if(data->player2->posc+1== 33 && data->bomber->plateau[data->player2->posl][0]!=0)
                    data->player2->posc = 32;
                else {
                data->player2->posc = data->player2->posc+1;
                }

                pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
            pthread_mutex_unlock(&dmutex);
            }

            else if (buf[0] == 'q'&& data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 1 && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 3
                     && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 6 && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 2
                     && data->bomber->plateau[data->player2->posl][data->player2->posc-1]!= 4) {
            if (data->bomber->plateau[data->player2->posl][data->player2->posc]!= 6){
                    pthread_mutex_lock(&dmutex);
                data->bomber->plateau[data->player2->posl][data->player2->posc]= 0;
                pthread_mutex_unlock(&dmutex);}

                 if (data->player2->posc-1== -1 && data->bomber->plateau[data->player2->posl][32]==0)
                {
                    data->player2->posc = 32;
                }
                else if(data->player2->posc-1== -1 && data->bomber->plateau[data->player2->posl][32]!=0)
                    data->player2->posc = 0;
                else {
                data->player2->posc = data->player2->posc-1;
                }
            pthread_mutex_lock(&dmutex);
            data->bomber->plateau[data->player2->posl][data->player2->posc]= 5;
            pthread_mutex_unlock(&dmutex);
            }

        buf[298]='0'+data->player->alive;
        buf[299]='0'+data->player2->alive;
        buf[300]='0'+game_fini(*data->bomber);
        buf[301]='0'+data->player->score;
        buf[302]='0'+data->player->nb_bombe;
        buf[303]='0'+data->player2->score;
        buf[304]='0'+data->player2->nb_bombe;
        for (int i = 0; i <data->bomber->lignes ; i++) {
                for (int j=0; j <data->bomber->colonnes ; j++){
        buf[1+i*data->bomber->colonnes+j] ='0'+data->bomber->plateau[i][j];
        }
        }

        sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other, slen);
        }
        /*system("cls");
         printf( "\n\n\n\n\n\n\n\n\n\n" );
         system("cls");*/
        afficher_plateau(*data->bomber,*data->player,*data->player2);
    if (data->player->alive==1 && data->player2->alive==1){
        if (data->player->score >>  data->player2->score)
            {printf("%s a gagne par le score de %.2f",data->player->nom,((float)data->player->score/(float)data->player->nb_bombe));
               strcpy(buf,data->player->nom);
            }
        else
            {printf("%s a gagne par le score de %.2f",data->player2->nom,((float)data->player2->score/(float)data->player2->nb_bombe));
            strcpy(buf,data->player2->nom);}
    }
    else if (data->player2->alive == 0)
        {printf("%s a gagne par le score de %.2f",data->player->nom,((float)data->player->score/(float)data->player->nb_bombe));
        strcpy(buf,data->player->nom); }
    else
        {printf("%s a gagne par le score de %.2f",data->player2->nom,((float)data->player2->score/(float)data->player2->nb_bombe));
            strcpy(buf,data->player2->nom);}
    //strcpy(buf,"jeu fini");
    sendto(s, buf, BUFLEN, 0, (struct sockaddr*) &si_other, slen);
    // pthread_mutex_unlock(&dmutex);
    Sleep(200);

 }

void *deplacer_bomber(void *arg) {

    data_score * data = (data_score *)arg;
    printf("donnez votre joueur 1 \n");
    scanf("%s",&data->player->nom);

    while(data->player->alive && !game_fini(*data->bomber) && data->player2->alive) {
        //pthread_mutex_lock(&dmutex);


        afficher_plateau(*data->bomber,*data->player,*data->player2);

        //pthread_mutex_unlock(&dmutex);

        Sleep(50);
    }
}
void *explo(void *arg) {

    data_score * data = (data_score *)arg;
    while (data->player->alive&& data->player2->alive && !game_fini(*data->bomber)){
    expo_bombe(data->bomber,data->player,data->player2,2);
Sleep(100);
    }
}

void *explo2(void *arg) {

    data_score * data = (data_score *)arg;
    while (data->player->alive && !game_fini(*data->bomber)&& data->player2->alive){

    expo_bombe2(data->bomber,data->player2,data->player,2);

Sleep(100);
    }
}


int main() {
    SOCKET s;
    struct sockaddr_in server;
	WSADATA wsa;




	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );

	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}

    data_t data;
    data_t data2;
    data_send_t datas;
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
    datas.s=s;

    time_t now;
    time(&now);

    pthread_t anim,clavier,bombe,bombe2,clavier2,udp;
    srand(time(0));

    player.alive=1;
    player.score=0;
    player.nb_bombe=0;

    player2.alive=1;
    player2.score=0;
    player2.nb_bombe=0;
	lire_plateau("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\plateau.txt",&bomber);



    placer_obstacles(&bomber);
    placer_bomber(&bomber,&player,1);
    placer_bomber(&bomber,&player2,2);
    pthread_create(&anim,NULL,deplacer_bomber,&datas);
   //pthread_create(&clavier,NULL,lire_clavier,&data);




    pthread_create(&clavier,NULL,lire_clavier,&datas);
    pthread_create(&clavier2,NULL,lire_clavier2,&datas);
    pthread_create(&bombe,NULL,explo,&datas);
    pthread_create(&bombe2,NULL,explo2,&datas);
    pthread_join(clavier2,NULL);

    //pthread_join(anim,NULL);



    //printf("score de : %.2f par %s le %s",((float)player.score/(float)player.nb_bombe),player.nom,  ctime(&now));
    //enregistrer("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\score.txt",bomber);

	closesocket(s);
	WSACleanup();

	return 0;

}
