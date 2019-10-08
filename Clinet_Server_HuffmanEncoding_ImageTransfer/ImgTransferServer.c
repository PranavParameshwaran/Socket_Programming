#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
	/*int c_socket;
	char buff[100];
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr = INADDR_ANY; //inet_addr(IP);
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 0;
	}*/
	int i=1;
	int s_socket, s_server;
	char buff[100];
	s_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in server,other;
	memset(&server,0,sizeof(server));
	memset(&other,0,sizeof(other));
	server.sin_family=AF_INET;
	server.sin_port=htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;	// if any IP is connecting with this IP for that we are using INADDR_ANY
	if(bind(s_socket,(struct sockaddr*)&server, sizeof(server)) == -1)
	{
		printf("Bind Error\n");
		return 0;
	}
	listen(s_socket,5);
	socklen_t add;
	add = sizeof(other);
	s_server = accept(s_socket,(struct sockaddr*)&other,&add);

	int size;
	/*read(s_server,&size,sizeof(size));
	char bufff[size];
	read(s_server,bufff,size);*/

	char charbuf[1];
	FILE *fp;
	fp=fopen("img.bmp","w"); // open a text file in read mode and store the file handle into fp
	//fopen("tab.txt","wb");
	char endoffile = '0';
	int check = 0;
	while(check==0)
	{
		recv(s_server, &endoffile, sizeof(&endoffile), 0);
		if(endoffile=='1')
		{
			check=1;
			break;
		}
		else
		{
			recv(s_server, charbuf, sizeof(charbuf), 0);
			fputc(charbuf[0],fp);
		}
	}
	printf("File received successfully\n");
	printf("Data Copied to img.bmp file\n");
	fclose(fp);
	
	close(s_server);
	close(s_socket);
	return 0;
}