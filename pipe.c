#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	int fd[2];
	pipe(fd);
	if(fork()==0){
		//child
		int n;
		read(fd[0],&n,sizeof(n));
		int arr[n];
		read(fd[0],&arr,sizeof(arr));
		int k=arr[n/2];
		//close(fd[0]);
		write(fd[1],&k,sizeof(k));
		char str[100];
		close(fd[1]);
		sleep(1);
		read(fd[0],&str,sizeof(str));
		printf("%s",str);
		close(fd[0]);
	}
	else{
		//parent
		int n;
		scanf("%d",&n);
		write(fd[1],&n,sizeof(n));
		int arr[n];
		int ans=-1;
		for(int i=0;i<n;i++)
			scanf("%d",&arr[i]);
		write(fd[1],&arr,sizeof(arr));
		//close(fd[1]);
		read(fd[0],&ans,sizeof(ans));
		printf("parent---> %d\n",ans);
		close(fd[0]);
		//open(fd[1]);
		char str[]="done";
		write(fd[1],&str,sizeof(str));
		close(fd[1]);
		wait(NULL);
	}
	return 0;
}