#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc,char *argv[]){
	int sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serverAddress;
	bzero(&serverAddress,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddress.sin_port = htons(10001);
	
	connect(sock,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
	char username[100];
	gets(username);
	char password[100];
	gets(password);
	send(sock,username,sizeof(username),0);
	send(sock,password,sizeof(password),0);
	int answer;
	recv(sock,&answer,sizeof(answer),0);
	printf("anser here --- >%d\n",answer);
	if(answer==0)
		printf("incorrect\n");
	else
		printf("correct\n");
	close(sock);
	return 0;
}
