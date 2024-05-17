#include<unistd.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

int flag = 1;

// void del()
// {
// 	kill(pid_1,16);
// 	kill(pid_2,17);
// 	falg=1;
// }

// void Int1()
// {
// 	printf("Child process %d is killed by parent\n", getpid());
// 	exit(0);
// }

// void Int2()
// {
// 		printf("Child process %d is killed by parent\n", getpid());
// 	exit(0);
// }

void waiting(int pid) {
	printf("Process %d waiting...\n", pid);
	while(flag);
}

void stop() {
	flag = 0;
}

int main()
{
	pid_t pid_1 = 0, pid_2 = 0;
	pid_1 = fork();
	if(pid_1 != 0) pid_2 = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	
	if (pid_1 < 0 || pid_2 < 0){
		printf("error in fork!");
	} else if (pid_1 == 0) {
		flag = 1;
		signal(16, stop);
		waiting(getpid());
		lockf(1, 1, 0);
		printf("Child process %d is killed by parent\n", getpid());
		lockf(1, 0, 0);
		exit(0);
	} else if (pid_2 == 0) {
		flag = 1;
		signal(17, stop);
		waiting(getpid());
		lockf(1, 1, 0);
		printf("Child process %d is killed by parent\n", getpid());
		lockf(1, 0, 0);
		exit(0);
	} else {
		flag = 1;
		waiting(getpid());
		kill(pid_1, 16);
		kill(pid_2, 17);
		wait(NULL);
		wait(NULL);
		printf("Parent process %d is killed\n", getpid());
		exit(0);
	}
	return 0;
}


