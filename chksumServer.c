// server side
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 9008
int main(void){
    char data[50];
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
    int msgLen = recv(newConnection, data, sizeof(data), 0); 
    if (msgLen < 0)
    {
        printf("Message Transfer failed\n");
    }
    else{
        printf("Msg recieved of length: %d\n", msgLen);
        printf("Client Says: %s\n", data);
    }
    close(newConnection);
    close(newBind);


    // verification    
    int segsize = 3;
    //printf("Enter segment size: ");
    //scanf("%d", &segsize);
    int wordlen = strlen(data);
    int sum[segsize];
    for (int i = 0; i < segsize; i++)
    {
        sum[i] = 0;
    }
    // testing sum
    for (int i = 0; i < segsize; i++)
    {
        printf("%d ", sum[i]);
    }printf("\n");
    for (int l = 0; l < wordlen; l=l+segsize)
    {
        int c = 0;
        for (int m = segsize-1; m >= 0; m--)
        {
            int n = data[l+m] - 48;
            int o = sum[m];

            sum[m] = (n + o + c)%2; // sum
            c = (n + o + c)/2;
        }
        
    }
    // complementing sum to get checksum
    char checksum[50];
    for (int i = 0; i < segsize; i++)
    {
        if(sum[i]==0){
            checksum[i] = '1';
        }
        else{
            checksum[i] = '0';
        }
    }
    // testing sum
    printf("check sum: %s\n", checksum);
     return 0;
    
    
}
