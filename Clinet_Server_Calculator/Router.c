#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

struct RT
{
	char name;
	char IP[100];
	bool can_connect[100];
};

struct RT r[4];

int ServerSide()
{
	int s_socket, s_server;
	char buff[100];
	char buff2[100];

	//gets(buff);
	//scanf("%s", &buff);
	s_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in server, other, client;
	memset(&server,0,sizeof(server));
	memset(&other,0,sizeof(other));
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr =inet_addr(IP_ad);	// if any IP is connecting with this IP for that we are using INADDR_ANY
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 1;
	}
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
		recv(s_server,buff2,sizeof(buff2),0);
		recv(s_server,buff,sizeof(buff),0);
		if(strcmp("own IP",buff2)==0)
		{
			printf("msg from client:%s\n", buff);	
		}
		else
		{
			ClientSide(buff2,buff);

		}
		scanf("%s", buff);
		send(s_server,buff,sizeof(buff),0);
		
		printf("msg from client:%s\n", buff2);
		if(strcmp(buff,"Q")==0)
			break;
	}
	
	close(s_server);
	close(s_socket);
	return 0;

}

int ClientSide(char IP_ad[], char message[])
{
	int c_socket;
	int flag=0;
	char buff[100];
	char buff2[100];
	strcpy(buff, message);
	strcpy(buff2,IP_ad);
	char buff2[100];
	for(int i=0;i<4;i++)
	{
		if(IP_ad==r[i].IP)
		{
			if(r[0].can_connect[i]==1)
				flag=1;
		} 
	}
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	if(flag==1)
	{
		client.sin_addr.s_addr =inet_addr(IP_ad);	// if any IP is connecting with this IP for that we are using INADDR_ANY
		if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
		{
			printf("Connection Issue\n");
			return 1;
		}
		send(c_socket,buff2,sizeof(buff2),0);
		send(c_socket,buff,sizeof(buff),0);
	}
	else
	{
		for(int i=0;i<4;i++)
		{
			if(r[0].can_connect[i]==1)
			{
				client.sin_addr.s_addr =inet_addr(r[i].IP);
				if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
				{
					printf("Connection Issue\n");
					return 1;
				}
				send(c_socket,buff2,sizeof(buff2),0);
				send(c_socket,buff,sizeof(buff),0);
			}
		}
	}
	close(c_socket);
	return 0;
}

int main()
{
	
	for(int i=0;i<4;i++)
	{
		switch(i)
		{
			case 0: r[i].name = 'A';
					r[i].IP = "Enter IP of comp 1";
					break;
			case 1: r[i].name = 'B';
					r[i].IP = "Enter IP of comp 2";
					break;
			case 2: r[i].name = 'C';
					r[i].IP = "Enter IP of comp 3";
					break;
			case 3: r[i].name = 'D';
					r[i].IP = "Enter IP of comp 4";
					break;
		}
	}
	printf("Do you want Send message to anyone\n");

	int er;
	er = ClientSide();
	if(er==1)
		printf("Error\n");
	
	close(s_server);
	close(s_socket);
	return 0;

}