#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int c_socket;

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

void Read();
void D2B(int value, int array[], int bits);
int B2D(int array[], int bits);
void BuildLookUpTable();
void CodeAssignment();



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






void Read()
{
	cout<<"\nEnter the string to encode and send : ";
	getline(cin,Text);
	
	int flag;
	
	for(int i=0;i<Text.length();i++)
	{
		flag=0;
		for(int j=0;j<size;j++)
		{
			if(Leaf[j].c==Text[i])
			{
				Leaf[j].Frequency++;
				flag=1;
				break;
			}
		}
		
		if(flag==0)
		{
			Leaf[size].c=Text[i];
			Leaf[size].Frequency=1;
			size++;
		}
	}

	send(c_socket, &size, sizeof(size), 0);
	
	int temp_frequency;
	char temp_c;

	for(int i=0;i<size;i++)
	{
		temp_frequency=Leaf[i].Frequency;
		temp_c=Leaf[i].c;

		send(c_socket, &temp_frequency, sizeof(temp_frequency), 0);
		send(c_socket, &temp_c, sizeof(temp_c), 0);
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


void CodeAssignment()
{
	int temp_code;
	cout<<endl<<"The encoding value sent : ";


	for(int i=0;i<Text.length();i++)
	{
		character=(int)Text[i];
		for(int j=0;j<No_Of_Bits;j++)
		{
			cout<<assignment[character][j];
			temp_code=assignment[character][j];
			send(c_socket, &temp_code, sizeof(temp_code), 0);
		}	
	}

	temp_code=-666;
	send(c_socket, &temp_code, sizeof(temp_code), 0);
	
	cout<<endl;
	
}


//////////////////////////////////////////////////








int main()
{

	//char buf[100]="";
	c_socket= socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in client;
	memset(&client, 0 , sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr=INADDR_ANY;
	//client.sin_addr.s_addr = inet_addr("172.16.17.77");

	if(connect(c_socket, (struct sockaddr *)&client, sizeof(client))==-1)
	{
		cout<<"Connection Issue\n";
		return 0;
	}

	//send(c_socket, buf, sizeof(buf), 0);
	//recv(c_socket, buf, sizeof(buf), 0);
	//cout<<"Message from Server : "<<buf<<endl;


	///////////////////////////////////////////////

	for(int i=0;i<128;i++)
	{
		assignment_value[i]=-6;
		for(int j=0;j<10;j++)
			assignment[i][j]=-666;
	}

	Read();
	BuildLookUpTable();
	CodeAssignment();

	///////////////////////////////////////////////
	
	close(c_socket);
	return 0;

}
