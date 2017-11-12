#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<signal.h>
#include<errno.h>

int main(int argc,char *argv[]){

	int sock=socket(PF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in serverAddress,clientAddress;

	bzero(&serverAddress,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port= htons(10001);
	
	int k=0;
	k=bind(sock,(struct sockaddr *) &serverAddress, sizeof(serverAddress));
	printf("a---> %d\n",k);
	if(k==-1)
		printf("error in binding\n");
	
	listen(sock,10);
	
	int clientsize = sizeof(clientAddress);
	while(1){
		int new_sock;
		if(fork()==0){
			new_sock=accept(sock,(struct sockaddr*)&clientAddress,&clientsize);
			char username[100]="";
			recv(new_sock,username,sizeof(username),0);
			printf("username -- > %s \n",username);
			char password[100]="";
			recv(new_sock,password,sizeof(password),0);
			printf("password -- > %s \n",password);

			int inside_sock=socket(AF_INET,SOCK_STREAM,0);
			struct sockaddr_in auther_server;
			

			bzero(&auther_server,sizeof(auther_server));
			auther_server.sin_family=AF_INET;
			auther_server.sin_addr.s_addr=inet_addr("127.0.0.1");
			auther_server.sin_port=htons(11000);

			connect(inside_sock,(struct sockaddr*)&auther_server,sizeof(auther_server));

			send(inside_sock,&username,sizeof(username),0);
			send(inside_sock,&password,sizeof(password),0);
			int ans;
			recv(inside_sock,&ans,sizeof(ans),0);
			printf("ans received---> %d\n",ans);
			send(new_sock,&ans,sizeof(ans),0);
		}
		else{
			wait(NULL);
			close(new_sock);
		}
	}
	return 0;
}