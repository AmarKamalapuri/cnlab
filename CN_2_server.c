//Server side C/C++ program to demonstrate Socket programming

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
	int n,maxx,sock_s,sock_c1,sock_c2,addr_size;
	struct sockaddr_in addr_s,addr_c1,addr_c2;
	char msg[2000];
	
	sock_s=socket(AF_INET,SOCK_STREAM,0);
	if(sock_s<0){printf("Some error occured\n"); return 0;}
	printf("Server socket created\n");
	memset(&addr_s,'\0',sizeof(addr_s));
	addr_s.sin_family=AF_INET;
	addr_s.sin_port=htons(8090);
	addr_s.sin_addr.s_addr=inet_addr(ip);
	
	n=bind(sock_s,(struct sockaddr*)&addr_s,sizeof(addr_s));
	if(n<0){printf("Some error occured\n"); return 0;}
	printf("Binded to the port\n");

	listen(sock_s,10);
	printf("Server is live now.....\n");
	
	fd_set clients;
	
	while(1)
	{
         FD_ZERO(&clients);
         FD_SET(sock_s,&clients);
         maxx=sock_s;
         int actv=select(maxx+1,&clients,NULL,NULL,NULL);
         
         if (FD_ISSET(sock_s, &clients))  
         {  
            sock_c1=accept(sock_s, (struct sockaddr *)&addr_c1, (socklen_t*)&addr_c1);
            if(sock_c1<0) {perror("Some error occured...."); return 0;}  
            printf("Client 1 added...!\n");  
         }
         FD_SET(sock_c1,&clients);
         if(sock_c1>maxx) maxx=sock_c1;
         actv=select(maxx+1,&clients,NULL,NULL,NULL);

         if (FD_ISSET(sock_s, &clients))  
         {  
            sock_c2=accept(sock_s, (struct sockaddr *)&addr_c2, (socklen_t*)&addr_c2);
            if (sock_c2<0) {perror("Some error occured...."); return 0;}  
            printf("Client 2 added...!\n");
         } 
         FD_SET(sock_c2,&clients);
         if(sock_c1>maxx) maxx=sock_c1;
         if(sock_c2>maxx) maxx=sock_c2;
         
         while(1)
         {
           bzero(msg,2000);
           recv(sock_c1,msg,2000,0);
           printf("Message sent from client 1 to client 2\n");
           send(sock_c2,msg,2000,0);
           
           bzero(msg,2000);
           recv(sock_c2,msg,2000,0);
           printf("Message sent from client 2 to client 1\n");
           send(sock_c1,msg,2000,0);
         }
         
        }
	return 0;
}
*/
