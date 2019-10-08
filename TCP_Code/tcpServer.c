#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int s_socket, s_server;
	char buff[100]="Helllo ClienT\n";
	char buff2[100];
	//gets(buff);
	//scanf("%s", &buff);
	s_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in server,other;
	memset(&server,0,sizeof(server));
	memset(&other,0,sizeof(other));
	server.sin_family=AF_INET;
	server.sin_port=htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;	// if any IP is connecting with this IP for that we are using INADDR_ANY
	bind(s_socket,(struct sockaddr*)&server, sizeof(server));
	listen(s_socket,5);
	socklen_t add;
	add = sizeof(other);
	s_server = accept(s_socket,(struct sockaddr*)&other,&add);
	while(1)
	{
		scanf("%s", buff);
		send(s_server,buff,sizeof(buff),0);
		recv(s_server,buff2,sizeof(buff2),0);
		printf("msg from client:%s\n", buff2);
		if(strcmp(buff,"Q")==0)
			break;
	}
	
	close(s_server);
	close(s_socket);
	return 0;

}