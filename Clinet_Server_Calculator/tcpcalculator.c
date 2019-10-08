#include<stdio.h>
//#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

//using namespace std;
int main()
{
	int c_socket;
	char buff[100];
	float input;
	int ch;
	float output;
	int flag=0;
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	//bcopy((char *)"172.16.17.114", (char *)&client.sin_addr.s_addr, length);  //inet_addr("172.16.17.77");
	client.sin_addr.s_addr =INADDR_ANY;	// if any IP is connecting with this IP for that we are using INADDR_ANY
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 0;
	}
	label:
		recv(c_socket,buff,sizeof(buff),0);
		printf("\n%s", buff);
		bzero(buff,100);
		scanf("%d", &ch);
		send(c_socket,&ch,sizeof(ch),0);

		recv(c_socket,buff,sizeof(buff),0);
		printf("%s\n",buff );
		bzero(buff,100);
		scanf("%f", &input);
		send(c_socket,&input,sizeof(input),0);

		recv(c_socket,buff,sizeof(buff),0);
		printf("%s\n",buff );
		bzero(buff,100);
		scanf("%f", &input);
		send(c_socket,&input,sizeof(input),0);

		recv(c_socket,buff,sizeof(buff),0);
		printf("%s", buff);
		recv(c_socket,&output,sizeof(output),0);
		printf("%f", output);
		bzero(buff,100);
	if(strcmp(buff,"Close")==0)
		flag=1;

	if(flag==0)
		goto label;
	close(c_socket);
	return 0;

	/*
	
         */

}