#include "jeu.h"
pthread_mutex_t dmutex = PTHREAD_MUTEX_INITIALIZER;


void *lire_clavier(void *arg){
    data_rec_t * data = (data_rec_t *)arg;

    int s=data->s;
    struct sockaddr_in si_other;
    int slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	char c;
    //int arrayToSend[data->bomber->lignes][data->bomber->colonnes];
    memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

    printf("donnez votre joueur 2 \n");
    scanf("%s",&data->player2->nom);
    strcpy(message,data->player2->nom);
    if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)

		{
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

     memset(buf,'\0', BUFLEN);
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}


    while(data->player->alive && data->player2->alive) {

        if (_kbhit()) {
            c = _getch();
            message[0]=c;
    }

     if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)

		{
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

     memset(buf,'\0', BUFLEN);
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}
        //puts(buf);
        printf("\n");
        for (int i = 0; i <data->bomber->lignes ; i++) {
                for (int j=0; j <data->bomber->colonnes ; j++){
        data->bomber->plateau[i][j]=(int)(buf[1+i*data->bomber->colonnes+j]-'0');
        }
        }
        message[0]='g';
        data->player->alive=(int)(buf[298]-'0');
        data->player2->alive=(int)(buf[299]-'0');

    afficher_plateau_client(*data->bomber);
    printf("\n %d", data->player->alive);
    printf("\n %d", data->player2->alive);

    }
       // pthread_mutex_unlock(&dmutex);

    /*if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}*/
		printf("done");
    Sleep(200);


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

/*void *cnx(void *arg){
    int * s = (int *)arg;
    struct sockaddr_in si_other;
    int slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];


	printf("Enter message : ");
		//gets(message);

		//send the message
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			//exit(EXIT_FAILURE);
		}

		puts(buf);

}*/


int main() {

	int s;
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}




    data_t data;
    data_t data2;
    data_rec_t datas;

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

    //placer_bomber(&bomber,&player,1);
    //placer_bomber(&bomber,&player2,2);
    //placer_obstacles(&bomber);

    //pthread_create(&anim,NULL,deplacer_bomber,&datas);
   /*pthread_create(&clavier,NULL,lire_clavier,&data);

    pthread_create(&clavier2,NULL,lire_clavier2,&data2);*/

    pthread_create(&clavier,NULL,lire_clavier,&datas);
    //pthread_create(&bombe,NULL,explo,&datas);
    //pthread_create(&bombe2,NULL,explo2,&datas);
    //pthread_create(&udp,NULL,cnx,&s);
    //pthread_join(clavier,NULL);
    pthread_join(clavier,NULL);

    //pthread_join(anim,NULL);



    printf("done");

    //printf("score de : %.2f par %s le %s",((float)player.score/(float)player.nb_bombe),player.nom,  ctime(&now));
    //enregistrer("C:\\Users\\abgad\\OneDrive\\Documents\\projetC\\score.txt",bomber);
	closesocket(s);
	WSACleanup();
	return 0;

	//il ya bug dans le score
}
