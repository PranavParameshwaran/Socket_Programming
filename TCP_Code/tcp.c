#include<stdio.h>
//#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<string.h>

//using namespace std;
int main()
{
	int c_socket;
	char buff[100]="Hello Server\n";
	char buff2[100];
	char IP[100]= "192.168.1.8";
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	//bcopy((char *)"172.16.17.114", (char *)&client.sin_addr.s_addr, length);
	client.sin_addr.s_addr =inet_addr(IP);	// if any IP is connecting with this IP for that we are using INADDR_ANY
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 0;
	}
	while(1)
	{
		recv(c_socket,buff2,sizeof(buff2),0);
		printf("msg from server:%s\n", buff2);
			if(strcmp(buff2,"Q")==0)
				break;
		scanf("%s", buff);
		send(c_socket,buff,sizeof(buff),0);
		
	}
	close(c_socket);
	return 0;

	/*
	
         */

}