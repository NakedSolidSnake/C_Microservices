// Server side implementation of UDP client-server model 
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

bool route(char *service, char *buffer);
bool getService(char *port, const char *service);
int ReadLine(char *buff, int size, FILE *fp);

// Driver code 
int main(int argc, char *argv[]) { 
	int sockfd;
    int port; 
	char buffer[MAXLINE]; 
	struct sockaddr_in servaddr, cliaddr; 

    if(argc != 2){
        fprintf(stderr, "Error.: Usage ./%s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

    port = atoi(argv[1]);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(port); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	int len, n; 

    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        len = sizeof(cliaddr); //len is value/resuslt 

        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                    &len); 
        buffer[n - 1] = '\0'; 
        if( route(buffer, buffer) == true)
        {           

            sendto(sockfd, (const char *)buffer, strlen(buffer), 
                MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
                    len);           
        }
    }

    return 0; 
} 

bool getService(char *port, const char *service)
{
    bool ret = false;
    char buffer[1024];
    char _port[5];
    char _service[10];    

    FILE *file = fopen("./mapping", "r");
    if(file == NULL)
        return ret;

    while(ReadLine(buffer, 1024, file)){
        memset(_port, 0, 5);
        memset(_service, 0, 10);
        sscanf(buffer, "%s\t%s", _port, _service);
        if(!strcmp(_service, service)){
            strncpy(port, _port, 5);
            ret = true;
        }
    }

    fclose(file);
    return ret;
}

int ReadLine(char *buff, int size, FILE *fp)
{
  buff[0] = '\0';
  buff[size - 1] = '\0';             /* mark end of buffer */
  char *tmp;

  if (fgets(buff, size, fp) == NULL) {
      *buff = '\0';                   /* EOF */
      return false;
  }
  else {
      /* remove newline */
      if ((tmp = strrchr(buff, '\n')) != NULL) {
        *tmp = '\0';
      }
  }
  return true;
}

bool route(char *service, char *buffer)
{
    bool ret;
    char port[5] = {0};
    ret = getService(port, service);
    if(ret){
        //sendto service        
        int sockfd;         
        char *hello = "Hello from client"; 
        struct sockaddr_in     servaddr; 
    
        // Creating socket file descriptor 
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        } 
    
        memset(&servaddr, 0, sizeof(servaddr)); 
        
        // Filling server information 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_port = htons(atoi(port)); 
        servaddr.sin_addr.s_addr = INADDR_ANY; 
        
        int n, len; 
        
        sendto(sockfd, (const char *)service, strlen(service), 
            MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
                sizeof(servaddr)); 
            
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, (struct sockaddr *) &servaddr, 
                    &len); 
        buffer[n] = '\0';     
        close(sockfd); 
    }

    return ret;
}