#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "desd_sock"

int main()
{
	int lfd, fd, ret;
	struct sockaddr_un serv_addr, cli_addr;
	socklen_t socklen = sizeof(serv_addr);
	char msg[128];
	//1. create listening server socket
	lfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(lfd < 0)
	{
		perror("server: socket() failed.");
		_exit(1);
	}
	printf("server: listening socket is ready.\n");
	//2. bind unix socket addr
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, SOCKET_PATH);
	ret = bind(lfd, (struct sockaddr*) &serv_addr, socklen);
	if(ret < 0)
	{
		perror("server: bind() failed.");
		_exit(1);
	}
	printf("server: socket is bound to UNIX socket addr : %s.\n", SOCKET_PATH);
	//3. listen to server socket
	listen(lfd, 5);
	printf("server: listening to server socket.\n");
	//6. accept client connection
	printf("server: waiting for client connection.\n");
	memset(&cli_addr, 0, sizeof(cli_addr));
	socklen = sizeof(cli_addr);
	fd = accept(lfd, (struct sockaddr*)&cli_addr, &socklen);
	if(fd < 0)
	{
		perror("server: accept() failed.");
		_exit(1);	
	}
	printf("server: client connection is accepted.\n");
	do {
		//8. read from client
		read(fd, msg, sizeof(msg));
		printf("client: %s\n", msg);
		//9. write to client
		printf("server: ");
		gets(msg);
		write(fd, msg, strlen(msg)+1);
	} while(strcmp(msg, "bye")!=0);
	//12. close socket
	printf("server: closing socket.\n");
	close(fd);
	//13. shutdown listening socket
	printf("server: closing listening socket.\n");
	shutdown(lfd, SHUT_RDWR);	
	return 0;	
}

