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
#include <dirent.h>

#define MAXLINE 1024

typedef struct 
{
    char port[6];
    char service[20];
} Service;

typedef struct
{
    Service services[10];
    int amount;
} ServiceMapping;

bool route(ServiceMapping *service_mapping, char *service, char *buffer);
bool getService(ServiceMapping *service_mapping, const char *service, char *port);
int ReadLine(char *buff, int size, FILE *fp);
bool loadServices(ServiceMapping *service_mapping);

// Driver code
int main(int argc, char *argv[])
{
    int sockfd;
    int port;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    ServiceMapping service_mapping = {0};

    if (argc != 2)
    {
        fprintf(stderr, "Error.: Usage ./%s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    loadServices(&service_mapping);

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
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
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len, n;

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        len = sizeof(cliaddr); //len is value/resuslt

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&cliaddr,
                     &len);
        buffer[n - 1] = '\0';
        if (route(&service_mapping, buffer, buffer) == true)
        {

            sendto(sockfd, (const char *)buffer, strlen(buffer),
                   MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                   len);
        }
    }

    return 0;
}

bool getService(ServiceMapping *service_mapping, const char *service, char *port)
{
    bool ret = false;
    
    for(int i = 0; i < service_mapping->amount; i++)
    {
        Service *s = &service_mapping->services[i];
        if(!strcmp(service, s->service))
        {
            strncpy(port, s->port, 6);
            ret = true;
            break;
        }
    }
    
    return ret;
}

int ReadLine(char *buff, int size, FILE *fp)
{
    buff[0] = '\0';
    buff[size - 1] = '\0'; /* mark end of buffer */
    char *tmp;

    if (fgets(buff, size, fp) == NULL)
    {
        *buff = '\0'; /* EOF */
        return false;
    }
    else
    {
        /* remove newline */
        if ((tmp = strrchr(buff, '\n')) != NULL)
        {
            *tmp = '\0';
        }
    }
    return true;
}

bool route(ServiceMapping *service_mapping, char *service, char *buffer)
{
    bool ret;
    char port[6] = {0};
    ret = getService(service_mapping, service, port);
    if (ret)
    {
        //sendto service
        int sockfd;
        struct sockaddr_in servaddr;

        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        // Filling server information
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(atoi(port));
        servaddr.sin_addr.s_addr = INADDR_ANY;

        int n;
        socklen_t len;

        sendto(sockfd, (const char *)service, strlen(service),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));

        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *)&servaddr,
                     &len);
        buffer[n] = '\0';
        close(sockfd);
    }

    return ret;
}

bool loadServices(ServiceMapping *service_mapping)
{
    struct dirent *de;

    DIR *dr = opendir("./conf");

    if (dr == NULL)
    {
        printf("Could not open current directory");
        return 0;
    }

    while ((de = readdir(dr)) != NULL)
    {
        if (!strcmp(strchr(de->d_name, '.'), ".conf"))
        {
            char filepath[40];
            char line[40];
            snprintf(filepath, 40, "conf/%s", de->d_name);
            FILE *file = fopen(filepath, "r");
            if(file)
            {
               while (ReadLine(line, 1024, file))
                {
                    Service *s = &service_mapping->services[service_mapping->amount];
                    sscanf(line, "%s\t%s", s->port, s->service);
                    service_mapping->amount++;
                }
                fclose(file);
            }
            else 
                printf("It was not possible to open file.\n");

             
        }
    }
    closedir(dr);
    return 0;
}