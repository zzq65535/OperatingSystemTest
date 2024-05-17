#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#define SHMKEY 75

int pid;
int *addr;

void Client()
{
    int i;
    int shmid = shmget(SHMKEY, 1024, 0777);
    addr = (int *)shmat(shmid, 0, 0);
    for(i = 9;i >= 0;i--)
    {
        while(*addr != -1);
        printf("(client)sent\n");
        *addr = i;
    }
    exit(0);
}

void Server()
{
    int shmid = shmget(SHMKEY, 1024, 0777|IPC_CREAT);
    addr = (int *)shmat(shmid, 0, 0);
    do
    {
        *addr = -1;
        while(*addr == -1);
        printf("(server)receive\n");
    }while(*addr);
    shmctl(shmid,IPC_RMID,0);
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