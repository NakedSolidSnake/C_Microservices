#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdbool.h>

#define MAXLINE 1024 

bool create_append(const char *port, const char *service);

int main(int argc, char *argv[]) { 
	int sockfd;
    int port; 
	char buffer[MAXLINE]; 
	char *message;
	struct sockaddr_in servaddr, cliaddr; 

    if(argc != 4){
        fprintf(stderr, "Error.: Usage ./%s <port> <service> <message>\n ", argv[0]);
        return EXIT_FAILURE;
    }

    if( create_append(argv[1], argv[2]) == false ) 
        return EXIT_FAILURE;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if ( sockfd < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

    port = atoi(argv[1]);
    message = argv[3];
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(port); 
	
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	socklen_t len, n; 

    while(1)
    {
        len = sizeof(cliaddr);

        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
        buffer[n] = '\0'; 

        memset(buffer, 0, MAXLINE);
        snprintf(buffer, MAXLINE, "Service on port %d. : Message: %s\n", port, message);

        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
    }
	
	return 0; 
} 

bool create_append(const char *port, const char *service)
{
    FILE *file = fopen("mapping", "a+");
    if(!file)
        return false;

    fprintf(file, "\n%s\t%s", port, service);
    fclose(file);
    return true;
}