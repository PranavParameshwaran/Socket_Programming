#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int s_socket, s_server;

//////////////////////////////////////////////////

#include<iostream>
#include<math.h>
#include<algorithm>
#include<string.h>

using namespace std;

struct node
{
	char c;
	int Frequency;	
};

int size=0;
int No_Of_Bits;

struct node Leaf[100];

int assignment[128][10];
int assignment_value[128];

bool condition(node n1, node n2)
{
	return(n1.Frequency<n2.Frequency);
}


//char Text[100]; 
string Text;

void RecieveRead();
void BuildLookUpTable();
void D2B(int value, int array[], int bits);
int B2D(int array[], int bits);
void Decode();



void D2B(int value, int array[], int bits)
{
	int temp=value;
	for(int i=0;i<bits;i++)
		array[i]=0;

	int p;
	for(int i=0;i<bits;i++)
	{
		p=bits-1-i;
		if( pow(2,p)<=temp )
		{
			array[i]=1;
			temp-=pow(2,p);
		}
	}
}

int B2D(int array[], int bits)
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






void RecieveRead()
{
	recv(s_server, &size, sizeof(size), 0);
	
	int temp_frequency;
	char temp_c;
	
	for(int i=0;i<size;i++)
	{
		recv(s_server, &temp_frequency, sizeof(temp_frequency), 0);
		recv(s_server, &temp_c, sizeof(temp_c), 0);
		
		Leaf[i].c=temp_c;
		Leaf[i].Frequency=temp_frequency;
	}
}

int character;


void BuildLookUpTable()
{
	sort(Leaf,Leaf+size,condition);
	
	cout<<"\ncode assignment : "<<endl;
	for(int i=0;i<size;i++)
		cout<<Leaf[i].c<<"--"<<Leaf[i].Frequency<<endl;

	if(size==1)
		No_Of_Bits=1;
	else
		No_Of_Bits=ceil(log2(size));

	for(int i=0;i<size;i++)
	{
		character=(int)Leaf[i].c;
		D2B(i,assignment[character],No_Of_Bits);
		assignment_value[character]=B2D(assignment[character],No_Of_Bits);
	}
			
	for(int i=0;i<size;i++)
	{			
		cout<<"code for "<<Leaf[i].c<<" is : ";
		character=(int)Leaf[i].c;
		for(int i=0;i<No_Of_Bits;i++)
			cout<<assignment[character][i];
		cout<<endl;
	}
	
}



void Decode()
{
	int code[50]; 
	int temp_code;
	int i=0;

	while(1)
	{
		recv(s_server, &temp_code, sizeof(temp_code), 0);
		if(temp_code==-666)
			break;
		else
		{
			code[i]=temp_code;
			i++;
		}
	}

	cout<<"\nThe decoded text is      : ";
	
	int label=0;
	int power=No_Of_Bits-1;
	char decodedChar;
	
	for(int j=0;j<i;j++)
	{
		if( power==0 )
		{
			label+=(code[j]*pow(2,power));
			for(int i=0;i<128;i++)
			{
				if(assignment_value[i]==label)
				{	
					decodedChar=(char)i;
					cout<<decodedChar;
					break;
				}
			}
			label=0;
			power=No_Of_Bits-1;
		}
		else
		{
			label+=(code[j]*pow(2,power));
			power--;

		}
	}
	cout<<endl;
	
}


//////////////////////////////////////////////////




int main()
{
	char Message[100];
	
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
	//cout<<"Message from Client : "<<buf<<endl;
	

	///////////////////////////////////////////

	for(int i=0;i<128;i++)
	{
		assignment_value[i]=-6;
		for(int j=0;j<10;j++)
			assignment[i][j]=-666;
	}

	RecieveRead();
	BuildLookUpTable();
	Decode();

	///////////////////////////////////////////

	close(s_server);
	close(s_socket);
	return 0;

}