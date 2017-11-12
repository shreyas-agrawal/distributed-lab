/*
Vinamra Maliwal
20144039
QQ-Develop a client-server program to implement a date-time server and client. Upon connection
establishment, the server should send its current date, time and CPU load information to its clients.
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


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
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	send(newSocket, &tm, sizeof(tm), 0);
	FILE *f = fopen("/proc/loadavg" , "r") ;
	char buffer[100000] ;
	fgets(buffer , sizeof(buffer) , f) ;
	send(newSocket , buffer , sizeof(buffer),0) ;
    close(newSocket);
  }
  
  return 0;
}
