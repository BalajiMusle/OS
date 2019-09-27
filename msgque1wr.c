#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgque1.h"

// writer / sender process
int main()
{
	int mqid;
	msg_t m1;
	
	// create a message queue
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);
	}

	// initialize the message
	m1.type = MSGTYPE;
	printf("writer: enter a string : ");
	scanf("%s", m1.data);
	
	// send the message
	msgsnd(mqid, &m1, MSGSZ, 0);

	printf("enter a key to terminated...\n");
	getchar();
	// destroy message queue
	msgctl(mqid, IPC_RMID, NULL);
	return 0;
}
