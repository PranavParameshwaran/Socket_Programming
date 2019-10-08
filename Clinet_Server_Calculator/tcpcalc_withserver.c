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
	int flag=0;
	int ch;
	char buff[100];
	//ch=htonl(ch);
	//int ch=htonl(ch1);
	float a,b,c;
	//scanf("%s",buff);
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
	label:
		strcpy(buff, "Enter Choice\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Exit\n");
		send(s_server,buff,sizeof(buff),0);
		recv(s_server,&ch,sizeof(ch),0);
		printf("Choice : %d\n",ch );
		bzero(buff,100);
		strcpy(buff, "Enter A: ");
		send(s_server,buff,sizeof(buff),0);
		recv(s_server,&a,sizeof(a),0);
		printf("A : %f\n",a );
		bzero(buff,100);
		strcpy(buff, "Enter B: ");
		send(s_server,buff,sizeof(buff),0);
		recv(s_server,&b,sizeof(b),0);
		printf("B : %f\n",b );
		switch(ch)
		{
			case 1: c=a+b;
					printf("C : %f\n",c );
					bzero(buff,100);
					strcpy(buff, "Output: ");
					send(s_server,buff,sizeof(buff),0);
					bzero(buff,100);
					send(s_server,&c,sizeof(c),0);
					
					break;

			case 2: c=a-b;
					
					printf("C : %f\n",c );
					bzero(buff,100);
					strcpy(buff, "Output: ");
					send(s_server,buff,sizeof(buff),0);
					bzero(buff,100);
					send(s_server,&c,sizeof(c),0);
					break;
			case 3: c=a*b;
					
					printf("C : %f\n",c );
					bzero(buff,100);
					strcpy(buff, "Output: ");
					send(s_server,buff,sizeof(buff),0);
					bzero(buff,100);
					send(s_server,&c,sizeof(c),0);
					break;
			case 4: c=a/b;
					
					printf("C : %f\n",c );
					bzero(buff,100);
					strcpy(buff, "Output: ");
					send(s_server,buff,sizeof(buff),0);
					bzero(buff,100);
					send(s_server,&c,sizeof(c),0);
					break;
			case 5: flag=1;
					strcpy(buff, "Close");
					send(s_server,buff,sizeof(buff),0);
					bzero(buff,100);
					c=-666;
					send(s_server,&c,sizeof(c),0);
					break;
		}

		
	if(flag==0)
		goto label;
	
	close(s_server);
	close(s_socket);
	return 0;

}