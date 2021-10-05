// Server side C/C++ program to demonstrate Socket programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include<arpa/inet.h>

int main()
{

	char *ip="127.0.0.1"; //localhost IP address
	int n,port=8081,sock_s,sock_c,addr_size;
	struct sockaddr_in addr_s,addr_c;
	char msg[2000];
	
	sock_s=socket(AF_INET,SOCK_STREAM,0);
	if(sock_s<0){printf("Some error occured\n"); return 0;}
	printf("Server socket created\n");
	memset(&addr_s,'\0',sizeof(addr_s));
	addr_s.sin_family=AF_INET;
	addr_s.sin_port=port;
	addr_s.sin_addr.s_addr=inet_addr(ip);
	
	n=bind(sock_s,(struct sockaddr*)&addr_s,sizeof(addr_s));
	if(n<0){printf("Some error occured\n"); return 0;}
	printf("Binded to the port number: %d\n",port);

	listen(sock_s,10);
	printf("Server is live now.....\n");
	
	while(1)
	{
          addr_size=sizeof(addr_c);
          sock_c=accept(sock_s,(struct sockaddr*)&addr_c,&addr_size);
          printf("Client connected...\n");
          bzero(msg,2000);
          strcpy(msg,"This messege is sent from server");
          send(sock_c,msg,2000,0);
          close(sock_c);
        }
	return 0;
}
