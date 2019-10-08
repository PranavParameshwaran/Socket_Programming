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


int checkRedundantBit(int index)
{
	if(ceil(log2(index))==floor(log2(index)))
		return 1;
	else
		return 0;
}



int main()
{
	int c_socket;
	//char buf[100]="Hello Server client connected to you !!!";
	c_socket= socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client;
	memset(&client, 0 , sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr=INADDR_ANY;
	//client.sin_addr.s_addr = inet_addr("172.16.17.77");

	if(connect(c_socket, (struct sockaddr *)&client, sizeof(client))==-1)
	{
		printf("Connection Issue\n");
		return 0;
	}

	//send(c_socket, buf, sizeof(buf), 0);
	//recv(c_socket, buf, sizeof(buf), 0);
	//printf("Message from Server : %s\n",buf );
	


	//////////////////////////////////////////

	int m,r;
	int inputMessage;
	int message[20];

	printf("Enter message bits size : ");
	scanf("%d",&m);

	for(int i=1;1;i++)
	{
		if( (pow(2,i) < m+i+1 ) && (pow(2,i+1) >= m+(i+1)+1 ) )
		{
			r=i+1;
			break;
		}
	} 

	printf("Enter the message       : ");
	scanf("%d",&inputMessage);

	for(int i=m;i>=1;i--)
		message[i]=(int)(inputMessage/pow(10,i-1))%10;


	int messageCoded_size;
	int messageCoded[30];
	
	int RIndex[20];
	int RArray[20][20];


	messageCoded_size=r+m;
	assignRArray(messageCoded_size,m,r,RArray);

	printf("\nRArray : \n");
	for(int i=0;i<r;i++)
	{
		printf("R%d : ",i+1);
		for(int k=0;k<messageCoded_size;k++)
		{
			if(RArray[i][k]==-666)
				break;
			else
				printf("%d ",RArray[i][k]);
		}
		printf("\n");
	}
	printf("\n");

	for(int i=0;i<r;i++)
		RIndex[i]=pow(2,i);


	int l=m;
	for(int i=messageCoded_size;i>=1;i--)
	{
		if(checkRedundantBit(i)==1)
		{
			messageCoded[i]=1;
		}
		else
		{
			messageCoded[i]=message[l];
			l--;
		}
	}


	printf("Redundant bit : \n");
	int check;
	for(int i=0;i<r;i++)
	{
		check=0;
		for(int j=0;1;j++)
		{
			if(RArray[i][j]==-666)
				break;
			else
				check^=messageCoded[RArray[i][j]];
		}

		if(check==1)
			messageCoded[RIndex[i]]=0;

		printf("parity bit R%d : %d\n",i+1,messageCoded[RIndex[i]]);
	}




	send(c_socket, &messageCoded_size, sizeof(messageCoded_size), 0);

	for(int i=messageCoded_size;i>=1;i--)
		send(c_socket, &messageCoded[i], sizeof(int), 0);

	
	printf("\nCODED Message with redundant bits : ");
	for(int i=messageCoded_size;i>=1;i--)
	{
		if(checkRedundantBit(i)==1)
			printf("R ");
		else
			printf("C ");
	}

	printf("\nCODED Message with redundant bits  : ");
	for(int i=messageCoded_size;i>=1;i--)
		printf("%d ",messageCoded[i]);
	printf("\n");


	//////////////////////////////////////////



	close(c_socket);
	return 0;

}
