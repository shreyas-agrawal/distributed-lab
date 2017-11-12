#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in auth_ser,clientAddress;
	bzero(&auth_ser,sizeof(auth_ser));
	auth_ser.sin_family=AF_INET;
	auth_ser.sin_port=htons(11000);

	int a=bind(sock,(struct sockaddr*)&auth_ser,sizeof(auth_ser));
	if(a==-1)
		printf("error in binding\n");

	listen(sock,10);
	int new_sock;
	while(1){
		int clientsize=sizeof(clientAddress);
		new_sock=accept(sock,(struct sockaddr*)&clientAddress,&clientsize);
		char username[]="abc";
		char password[]="123";
		char rev_user[100]="";
		char rev_pass[100]="";
		recv(new_sock,&rev_user,sizeof(rev_user),0);
		recv(new_sock,&rev_pass,sizeof(rev_pass),0);
		printf("received username %s\n",rev_user);
		printf("received password %s\n",rev_pass);
		int temp=-1;
		for(int i=0;i<strlen(rev_user);i++){
			if(username[i]!=rev_user[i]){
				temp=1;
				break;
			}
		}
		for (int i = 0; i < strlen(rev_pass); ++i)
		{
			if(password[i]!=rev_pass[i]){
				temp=1;
				break;
			}
		}
		int ans;
		if(temp==1){
			ans=0;
			printf("here ans= %d\n",ans);
			send(new_sock,&ans,sizeof(ans),0);
		}
		else{
			ans=1;
			printf("here ans==%d \n",ans);
			send(new_sock,&ans,sizeof(ans),0);
		}
	}
	close(new_sock);
	return 0;
}