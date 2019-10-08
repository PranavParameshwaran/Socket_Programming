#include<stdio.h>
//#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include <math.h>

//using namespace std;
int main()
{
	int c_socket;
	char buff[100];
	//ACTUAL CODE
	int key[10];
	int keyval,keysize,power,powerprev;
	int val=0;
	printf("Enter key and size of key\n");
	scanf("%d %d",&keyval,&keysize);
	for(int i=0;i<keysize;i++)
	{
		power = pow(10,i+1);
		powerprev = pow(10,i);
		val = (int)((keyval%power)/powerprev);
		key[i] = val;
	}
	/*printf("KEY ARRAY\n");
	for(int i=keysize-1;i>=0;i--)
		printf("%d ", key[i]);*/
	int Data,datasize;
	printf("Enter data and size of data\n");
	scanf("%d %d",&Data,&datasize);
	int data[100];
	val=0;
	int counti=0;
	for(int i=0;i<keysize-1;i++)
	{
		data[i] = 0;
		counti++;
	}

	for(int i=0;i<datasize;i++)
	{
		power = pow(10,i+1);
		powerprev = pow(10,i);
		val = (int)((Data%power)/powerprev);
		data[counti+i] = val;
	
	}
	int totsize = datasize+keysize-1;
	/*printf("\nDATA ARRAY\n");
	for(int i=totsize-1;i>=0;i--)
		printf("%d ", data[i]);*/
	int data_copy[100];
	//printf("TOT SIZE %d\n",totsize-1 );
	for(int i=totsize-1;i>=0;i--)
		data_copy[i] = data[i];

	int Quo;
	int count=0;
	int k=totsize-1;
	int init=0;
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
	for(int i=0;i<keysize-1;i++)
	{
		data[i] = data_copy[i];
		printf("%d", data_copy[i]);
	}
	printf("\n");

	// ACTUAL CODE ENDS HERE
	/*printf("\nFinal answer\n");
	for(int i=totsize-1;i>=0;i--)
		printf("%d ",data[i]);
	printf("\n");*/

	//char buff2[100];
	//char IP[100]= "192.168.1.8";
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	//bcopy((char *)"172.16.17.114", (char *)&client.sin_addr.s_addr, length);
	client.sin_addr.s_addr =INADDR_ANY;	// if any IP is connecting with this IP for that we are using INADDR_ANY
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 0;
	}
	printf("Sending\n");
	send(c_socket,key,sizeof(key),0);
	send(c_socket,&keysize,sizeof(keysize),0);
	send(c_socket,data,sizeof(data),0);
	send(c_socket,&datasize,sizeof(datasize),0);
	recv(c_socket,buff,sizeof(buff),0);
	printf("msg from server:%s\n", buff);
		
	close(c_socket);
	return 0;

	/*
	
         */

}