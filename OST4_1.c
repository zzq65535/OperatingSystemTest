#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MSGKEY 75

struct msgform
{
    long mtype;
    char mtext[1024];
};

int msgqid,pid;
void Client()
{
    struct msgform msg;
    int i;
    msgqid = msgget(MSGKEY,0777);
    for(i = 10; i >= 1; i--)
    {
        for(int j = 1; j <= 1E7; j++);
        msg.mtype = i;
        char t[] = "helloworld";
        strcpy(msg.mtext, t);
        printf("(client)sent: %d\n", i);
        msgsnd(msgqid,&msg,1024,0);
    }
    exit(0);
}

void Server()
{
    msgqid= msgget(MSGKEY, 0777 | IPC_CREAT);
    struct msgform msg;
    do
    {
        msgrcv(msgqid, &msg, 1024, 0, 0);
        printf("(server)receive: %ld, %s\n", msg.mtype, msg.mtext);
    }while(msg.mtype != 1);
    msgctl(msgqid,IPC_RMID,0);
    exit(0);
}

int main()
{
    while((pid = fork()) ==-1);
    if(!pid) Server();
    while((pid = fork()) ==-1);
    if(!pid) Client();
    wait(0);
    wait(0);
    return 0;
}