#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
struct node
{
	char IP[6][30] ;
	int port[6] ;
	int len ;
} table ;
int main(){
  int clientSocket, portNum, nBytes;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 7891;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  recv(clientSocket, &table , sizeof(table) , 0);

  int i ;
  for( i = 0 ; i<table.len ; i++)
  {
  	printf("Node : %d , IP= %s and Port= %d\n" , i+1, table.IP[i] , table.port[i]) ;
  }
  return 0;
}
