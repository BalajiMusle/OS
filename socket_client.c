#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "desd_sock"

int main()
{
	int cfd, ret;
	char msg[128];
	struct sockaddr_un serv_addr;
	socklen_t socklen = sizeof(serv_addr);
	//4. create client socket
	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(cfd < 0)
	{
		perror("client: socket() failed.");
		_exit(1);
	}
	printf("client: client socket is ready.\n");
	//5. connect to server unix socket
	printf("client: connecting to server socket.\n");
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, SOCKET_PATH);
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




