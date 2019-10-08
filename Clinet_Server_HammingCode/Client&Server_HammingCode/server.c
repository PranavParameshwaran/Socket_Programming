#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <math.h>



int getBitOfBinary(int x,int position,int bits)
{
	int Binary[20];
	int value=x;

	for(int i=bits-1;i>=0;i--)
	{
		if(pow(2,i)<=value)
		{
			Binary[i]=1;
			value=value-pow(2,i);
		}
		else
			Binary[i]=0;
	}

	return(Binary[position]);

}


void assignRArray(int size,int m, int r,int array[][20])
{
	for(int i=0;i<r;i++)
		for(int j=0;j<size;j++)
			array[i][j]=-666;

	int j;
	for(int i=0;i<r;i++)
	{
		j=0;
		for(int k=1;k<=size;k++)
		{
			if(getBitOfBinary(k,i,r)==1)
			{
				array[i][j]=k;
				j++;
			}
		}
	}
}


int BinaryToDecimal(int array[], int bits)
{
	int value=0;
	int p;

	for(int i=0;i<bits;i++)
	{
		p=bits-1-i;
		value+=array[i]*pow(2,p);
	}
	return value;
}





int main()
{
	char Message[100];
	int s_socket, s_server;
	//char buf[100]="Connection to Server established ..............!!!";
	
	s_socket= socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server, other;
	memset(&server, 0 , sizeof(server));
	memset(&other, 0 , sizeof(other));

	server.sin_family=AF_INET;
	server.sin_port=htons(9009);
	server.sin_addr.s_addr=INADDR_ANY;

	bind(s_socket, (struct sockaddr *)&server, sizeof(server));
	listen(s_socket, 5);

	socklen_t add;
	add=sizeof(other);
	s_server=accept(s_socket, (struct sockaddr *)&other, &add);

	//send(s_server, buf, sizeof(buf), 0);
	//recv(s_server, buf, sizeof(buf), 0);
	
	//printf("Message from Client : %s\n",buf );



	////////////////////////////////////////////////

	int messageReceived_size;
	int messageReceived[20];

	recv(s_server, &messageReceived_size, sizeof(messageReceived_size), 0);

	for(int i=messageReceived_size;i>=1;i--)
		recv(s_server, &messageReceived[i], sizeof(int), 0);


	//********************************
	//making error in received message
	messageReceived[5]=1;
	//********************************

	printf("\ncoded message received : ");
	for(int i=messageReceived_size;i>=1;i--)
		printf("%d ",messageReceived[i]);
	printf("\n");



	int redundantCheck[10];
	int r=ceil(log2(messageReceived_size));
	int m=messageReceived_size-r;

	int RIndex[20];
	int RArray[20][20];
	
	for(int i=0;i<r;i++)
		RIndex[i]=pow(2,i);

	assignRArray(messageReceived_size,m,r,RArray);


	int errorValue[20];
	int errorIndex;

	printf("\nRedundant bit check : \n");
	int check;
	for(int i=0;i<r;i++)
	{
		check=0;
		for(int j=0;1;j++)
		{
			if(RArray[i][j]==-666)
				break;
			else
				check^=messageReceived[RArray[i][j]];
		}
		printf("parity of R%d : %d\n",i+1,check);
		errorValue[(r-1)-i]=check;
	}

	errorIndex=BinaryToDecimal(errorValue,r);

	printf("\nError occured in %dth bit\n",errorIndex);
	printf("corrected message      : ");
	if(messageReceived[errorIndex]==1)
		messageReceived[errorIndex]=0;
	else
		messageReceived[errorIndex]=1;


	for(int i=messageReceived_size;i>=1;i--)
		printf("%d ",messageReceived[i]);
	printf("\n");
	
	////////////////////////////////////////////////


	close(s_server);
	close(s_socket);
	return 0;

}