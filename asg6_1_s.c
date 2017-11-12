/*
Vinamra Maliwal
20144039
QQQ---Implement a client-server program in which the server accepts a connection from a client and
updates it own Master table by adding the client information and send the updated table to client, so
client can update their own table
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

struct node
{
	char IP[6][30] ;
	int port[6] ;
	int len ;
} table ;
int main(){
  int welcomeSocket, newSocket, portNum, clientLen, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_in client;
  socklen_t addr_size;

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 7891;
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  addr_size = sizeof client;
  int i ;
  for(i=0 ; i<5 ; i++)
  {
    newSocket = accept(welcomeSocket, (struct sockaddr *) &client, &addr_size);
	table.port[table.len] = (int)(ntohs(client.sin_port)) ;
	inet_ntop(AF_INET , &(client.sin_addr) , table.IP[table.len] , INET_ADDRSTRLEN) ;	
	table.len +=1 ;
	send(newSocket, &table, sizeof(table), 0);
    close(newSocket);
  }
  
  return 0;
}
