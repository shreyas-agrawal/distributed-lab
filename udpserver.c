#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *args[]) {
	
	int sockid = socket(PF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serverAddr, clientAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5009);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sockid, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	
	while(1) {
		char buff[1000] = {0};
		int size = sizeof(serverAddr);
		int rbytes = recvfrom(sockid, buff, 1000, 0, (struct sockaddr *)&clientAddr, &size);
		int i;
		printf("String recieved: %s\n",buff);
		int length=strlen(buff);
	     for(i=0;i<length;i++)
	     {
	     	buff[i]=toupper(buff[i]);;
	     }
	     buff[length]=0;
		char ok[]="Got the message";
		size = sizeof(clientAddr);
		sendto(sockid, buff, strlen(buff), 0, (struct sockaddr *)&clientAddr, size);
	}
	close(sockid);
	return 0;
}
