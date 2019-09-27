#ifndef __MSGQUE1_H
#define __MSGQUE1_H

#define MQ_KEY	0x2809
#define MSGTYPE	2

typedef struct msg
{
	long type;
	char data[20];
}msg_t;

#define MSGSZ (sizeof(struct msg) - sizeof(long))

#endif


