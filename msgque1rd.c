#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msgque1.h"

// reader / receiver process
int main()
{
	int mqid;
	msg_t m2;

	// get the id of the msg que
	mqid = msgget(MQ_KEY, 0);
	if(mqid < 0)
	{
		perror("msgget() failed");
		_exit(1);
	}

	// receive message
	printf("reader: waiting for message...\n");
	msgrcv(mqid, &m2, MSGSZ, MSGTYPE, 0);
	printf("reader: msg received : %s\n", m2.data);
	return 0;
}
