#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/poll.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
enum{ PREAD,PWRITE};
bool g_exit = false;
void sig(int sig){
	printf("sigint\n");
	g_exit = true;
}
int make_child(int pip[],int delay,char * msg){
	if(pipe(pip) == -1)
		return -1;

	int pid = fork();
	switch(pid){
		case -1:
			close(pip[PWRITE]);
			pip[PWRITE] = -1;
			perror("child");
			return -1;
			break;
		case 0:
			goto child;
			break;
		default:
			close(pip[PWRITE]);
			pip[PWRITE] = -1;
			return pid;
			break;
	}
child:
	close(pip[PREAD]);
	int len = strlen(msg);
	for(;;){
		sleep(delay);
		printf("writing from %s\n",msg);
		if(write(pip[PWRITE],msg,len)<0)
			perror("write");
	}
	/*cant come*/
	exit(-1);
	return 0;
}

int main (void)
{
	signal(SIGINT,sig);
	struct pollfd pfds[2];
	int pipA[2] = {-1,-1}, pipB[2] = {-1,-1};
	int pidA = make_child(pipA,1,"AA");
	if(pidA == -1){
		perror("A failed");
		goto end;
	}
	int pidB = make_child(pipB,3,"BB");
	if(pidB == -1){
		kill(pidA,SIGKILL);
		perror("B failed");
		goto end;
	}

	pfds[0].fd = pipA[PREAD];
	pfds[0].events = POLLIN;
	pfds[1].fd = pipB[PREAD];
	pfds[1].events = POLLIN;
	
	while(!g_exit){
		char buf[1024];
		int nread;
		int ret = poll(pfds,2,100);
		if(ret < 0 )
			perror("poll fail");
		if( pfds[0].revents & POLLIN){
			nread = read(pipA[PREAD], buf, 1024);
			buf[nread] = '\0';
			printf("A head: %s\n",buf);
		}
		if( pfds[1].revents & POLLIN){
			nread = read(pipB[PREAD], buf, 1024);
			buf[nread] = '\0';
			printf("B head: %s\n",buf);
		}
	}
end:	
	if(pidA != -1)
		kill(pidA,SIGKILL);
	if(pidB != -1)
		kill(pidB,SIGKILL);

	if(pipA[PREAD] != -1)
		close(pipA[PREAD]);
	if(pipB[PREAD] != -1)
		close(pipB[PREAD]);

}
