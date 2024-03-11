// chat server
// normal server program
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 9008
int main(void){
    char buff[50];
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
    struct sockaddr_in server, new_conn;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Binding the socket to localhost
    int newBind = bind(newSocket, (struct sockaddr*) &server, sizeof(server));
    if (newBind < 0)
    {
        printf("Bind unsuccessful\n");
    }
    else{
        printf("Bind success\n");
    }

    int newListen = listen(newSocket, 1); // Second argument: the number of client requests to be handled
    if (newListen < 0)
    {
        printf("Port not listening\n");
    }
    else{
        printf("Port listening\n");
    }


    // Accepting the incoming connections
    int new_connLen = sizeof(new_conn);
    int newConnection = accept(newSocket, (struct sockaddr*) &new_conn, &new_connLen);
    if (newConnection < 0)
    {
        printf("Connection not accepted\n");
    }
    else{
        printf("Connection accepted\n");
        printf("Connection descriptor: %d\n", newConnection);
    }
    // recieving data and storing into buffer
    do{
    	//memset(buff, '\0', 48);
    	printf("Enter server msg: ");
    	fflush(stdin);
        gets(buff);
    	//scanf("%[^\n]s", buff);
    	send(newConnection, buff, sizeof(buff), 0);
    	//memset(buff, '\0', 48);
    	recv(newConnection, buff, sizeof(buff), 0);
    	printf("Client Says: %s\n", buff);
    }while(strcmp(buff, "bye") != 0);

    /*
    int msgLen = recv(newConnection, buff, sizeof(buff), 0); 
    if (msgLen < 0)
    {
        printf("Message Transfer failed\n");
    }
    else{
        printf("Msg recieved of length: %d\n", msgLen);
        printf("Client Says: %s\n", buff);
    }
    */
    close(newConnection);
    close(newBind);
     return 0;
    
    
}
