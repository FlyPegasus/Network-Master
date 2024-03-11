// chat client
// normal client program
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 9008
int main(void){
    struct sockaddr_in server;
    char msg[50];
    // Initializing Socket
    /*
        AF_INET[domain]: address family(IPv4 / IPv6)
        SOCK_STREAM[communication type]: connection oriented socket (TCP)
        SOCK_DGRAM[communication type]: UDP
        0[protocol]: default protocol of system
        IPPROTO_TCP[protocol]: using the TCP protocol
    */
    int newSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (newSocket < 0)
    {
        printf("Failed\n");
    }
    else{
        printf("Success\n");
    }

    // Initialize environment for sockaddr structure
    /*
        inet_addr("ip") can be replaced by Macro INADDR_ANY
    */
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connecting to server
    int newConnection = connect(newSocket, (struct sockaddr*) &server, sizeof(server));
    if (newConnection < 0)
    {
        printf("Connection Failed\n");
    }
    else{
        printf("Connected\n");
        do{
        	//memset(msg, '\0', 48);
        	recv(newConnection, msg, sizeof(msg), 0);
        	printf("Server Says: %s\n", msg);
        	//memset(msg, '\0', 48);
        	
        	printf("Enter your message: ");
	        fflush(stdin);
            gets(msg);
            //scanf("%[^\n]s", msg);
	        send(newSocket, msg, sizeof(msg), 0);
        }while(strcmp(msg, "bye") != 0);
        /*printf("Enter your message: ");
        scanf("%[^\n]s", msg);
        send(newSocket, msg, sizeof(msg), 0);*/
    }
    close(newSocket);

     return 0;
}
