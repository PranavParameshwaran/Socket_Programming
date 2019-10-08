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
//	char buff[100]="Helllo ClienT\n";
	char buff2[100];
	//ACTUAL CODE
	
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

	int data_copy[100];
	int key[100];
	int keysize;
	int datasize;
	recv(s_server,key,sizeof(key),0);
	recv(s_server,&keysize,sizeof(keysize),0);
	recv(s_server,data_copy,sizeof(data_copy),0);
	recv(s_server,&datasize,sizeof(datasize),0);
	int totsize = datasize +keysize-1;
	int count=0;
	int k=totsize-1;
	int init=0;
	//data_copy[5] = 1;
	while(k>=keysize-1)
	{ 
		count=0;
		//printf("%d\n",k );
		for(int i=k,j=keysize-1;i>=0,j>=0;i--,j--)
		{
			/*printf("DATA _ %d %d\n",data_copy[i],i);
			printf("KEY _ %d %d\n",key[j],j);*/
			if(data_copy[i]==0 && key[j]==1 && init==0)
			{}
			else
			{	data_copy[i] = data_copy[i] ^ key[j];
				init=1;
			}
			//printf("\n%d\n",data_copy[i]);
		}

		for(int i=k;i>=0;i--)
		{
			if(data_copy[i]==0)
				count++;
			else break;
		}

		k = k-count;
	}
	int flag=0;
	for(int i=0;i<totsize;i++)
	{
		if(data_copy[i] ==1)
			flag=1;
	}
	if(flag==0)
	{	printf("No error\n");
		strcpy(buff2,"No error\n");
		send(s_server,buff2,sizeof(buff2),0);
		
	}
	else
	{
		printf("Error in input\n");
		strcpy(buff2,"Error in input\n");
		send(s_server,buff2,sizeof(buff2),0);
	}

	
	close(s_server);
	close(s_socket);
	return 0;

}