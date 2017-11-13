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

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(5008);
	clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockid, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
	
	while(1) {
		char buff[1000];
		printf("Enter message to be translated\n");
		scanf("%s",buff);
		int size = sizeof(serverAddr);
		sendto(sockid, buff, strlen(buff),0, (struct sockaddr *)&serverAddr, size);
		int rbytes = recvfrom(sockid, buff, 1000, 0, (struct sockaddr *)&serverAddr, &size);
		printf("Message in upper case:\t%s\n",buff);
	}
	close(sockid);
	return 0;
}
