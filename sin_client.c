#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define SERVER_IP	"127.0.0.1"
#define SERVER_PORT	2809

int main()
{
	int cfd, ret;
	char msg[128];
	struct sockaddr_in serv_addr;
	socklen_t socklen = sizeof(serv_addr);
	//4. create client socket
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(cfd < 0)
	{
		perror("client: socket() failed.");
		_exit(1);
	}
	printf("client: client socket is ready.\n");
	//5. connect to server unix socket
	printf("client: connecting to server socket.\n");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =htons(SERVER_PORT);
	inet_aton(SERVER_IP, &serv_addr.sin_addr);
	ret = connect(cfd, (struct sockaddr*)&serv_addr, socklen);
	if(ret < 0)
	{
		perror("server: bind() failed.");
		_exit(1);
	}
	printf("client: connected to server socket.\n");
	do {
		//7. write to server
		printf("client: ");
		gets(msg);
		write(cfd, msg, strlen(msg)+1);
		//10. read from server
		read(cfd, msg, sizeof(msg));
		printf("server: %s\n", msg);
	} while(strcmp(msg, "bye")!=0);
	//11. close
	printf("client: closing client socket.\n");
	close(cfd);
	return 0;	
}




