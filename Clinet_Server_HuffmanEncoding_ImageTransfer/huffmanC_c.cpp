#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<math.h>


using namespace std;

int LookUp[128][100];

struct Node
{
	char c;
	int freq;
	int corres;

}n[100];

//******************************************
bool freqsort(node n1,node n2)
{
	return (n1.freq < n2.freq);
}

//******************************************
void D2B(int Lookup[], int Num, int Size) // 
{
	for(int j=Size-1;j>=0;j--)
		if(Num>pow(2,j))
			Lookup[j] = 1;
		else
			Lookup[j] = 0;
}
//*******************************************
int B2D(int Lookup[], int Val, int Size) // 
{
	int Value=0;
	for(int i=0;i<Size;i++)
		Value+=Lookup[i]*pow(2,Size-i-1);

	return Value;
}

//*******************************************
int beg=-1;
int endd=-1;
int ToTSize;
void TotWork()
{
	string text;
	cout<<"Enter the String\n";
	getline(cin,text);

	int chk=0;
	for(int i=0;i<text.length();i++)
	{
		chk=0;
		for(int j=0;j<=endd;j++)
		{
			if(n[j].c==text[i])
			{
				n[j].freq+=1;
				//l[j].freqi+=1;
				chk=1;
				break;
			}
		}
		if(beg==-1)
			beg=0;
		if(chk==0)
		{
			endd++;
			n[endd].c=text[i];
			/*l[ToTSize].var = text[i];
			l[ToTSize].freqi = 1;*/
			n[endd].freq=1;
			//n[endd].corres=endd;
			ToTSize++;			
		}
	}

	sort(n,n+(endd+1),freqsort);
	for(int i=0;i<ToTSize;i++)
		n[i].corres=i;

	// TO construct Lookup table for the input

	int Siz=ceil(log2(ToTSize));

	for(int i=0;i<ToTSize;i++)
		// INCOMPLETE




}

//*********  MAIN  *********************

int main()
{
	for(int i=0;i<128;i++)
	for(int j=0;j<10;j++)
	dict[i][j]=-666;

	int a[10];
	Huffman h;
	h.read();
	h.Huffmantree();
	h.code(hptr,a,0);
	print(hptr);
	cout<<"-----LOOKUP--------\n";
	look();
	cout<<"------Encoded Input--------\n";
	h.encodeInput();
	cout<<"\n------------------\n";

	/*cout<<"\nThe Decoded format for the given input is ";
	h.decode(hptr);
	cout<<endl;*/
	// ******** CLIENT SIDE CODE BELOW ***********
	
	int c_socket;
	char IP[100]= "10.42.0.1";
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	//bcopy((char *)"172.16.17.114", (char *)&client.sin_addr.s_addr, length);
	client.sin_addr.s_addr =inet_addr(IP);	// if any IP is connecting with this IP for that we are using INADDR_ANY
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 0;
	}
	int i=0;
	send(c_socket,&ToTSize,sizeof(ToTSize),0);
	send(c_socket,&i,sizeof(i),0);
	while(i<ToTSize)
	{
		send(c_socket,&l[i].var,sizeof(l[i].var),0);
		send(c_socket,&l[i].freqi,sizeof(l[i].freqi),0);
		i++;
		//send(c_socket,&i,sizeof(i),0);	
	}
	send(c_socket,eIn,sizeof(eIn),0);

	close(c_socket);
	return 0;
	
}


