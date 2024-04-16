// client side
/*
send the checksum to server
*/
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 9008
int main(void){
    char data[50];
    char word[50];
    printf("Enter word: ");
    gets(word);
    int segsize = 3;
    printf("Enter segment size: ");
    scanf("%d", &segsize);
    int wordlen = strlen(word);
    if (wordlen%segsize!=0)
    {
        /* append zeroes to front */
        int i = segsize - wordlen%segsize;
        for (int j = 0; j < i; j++)
        {
            data[j] = '0';
        }
        strcat(data, word);
        printf("operable data ready: %s\n", data);
    }
    wordlen = strlen(data);
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
    // making the codeword
    strcat(data, checksum);
    printf("codeword: %s\n", data);

    // sending codeword
    struct sockaddr_in server;
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
        send(newSocket, data, sizeof(data), 0);
    }
    close(newSocket);

     return 0;
}
