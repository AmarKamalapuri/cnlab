// Client side C/C++ program to demonstrate Socket programming

#include<stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include<arpa/inet.h>


int main()
{
	char *ip="127.0.0.1"; //localhost
	int n,port=8081,sock_c,addr_size;
	struct sockaddr_in addr_c;
	char msg[2000];
	
	sock_c=socket(AF_INET,SOCK_STREAM,0);
	if(sock_c<0){printf("Some error occured\n"); return 0;}
	
	memset(&addr_c,'\0',sizeof(addr_c));
	addr_c.sin_family=AF_INET;
	addr_c.sin_port=port;
	addr_c.sin_addr.s_addr=inet_addr(ip);
	
	connect(sock_c,(struct sockaddr*)&addr_c,sizeof(addr_c));
	printf("Server is connected...\n");
        recv(sock_c,msg,2000,0);
        printf("%s\n",msg);
	return 0;
}
