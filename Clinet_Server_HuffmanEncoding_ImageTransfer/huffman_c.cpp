#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>


using namespace std;

//******************************************
struct node
{
	char c;
	int freq;
	struct node *lcptr;
	struct node *rcptr;
	int encode[100];
	
}n[100],*hptr;

struct LT
{
	char var;
	int freqi;
}l[100];

//******************************************

int endd=-1;
int beg=-1;
int dict[128][100];
int eTTop=0;
int ToTSize;
int eIn[1000];

//*******    FREQSORT   *********************
bool freqsort(node n1,node n2)
{
	return (n1.freq < n2.freq);
}

//*********   Class  ***********************
class Huffman
{
	private:
		string text;
		int eInput[1000];
		
	public:
		
		
		void read();
		void Huffmantree();
		void code(struct node *ptr,int arr[],int top);
		void decode(struct node *ptr);
		void encodeInput();
};

//*******   Func Defn. ********************

void Huffman::read()
{
	cout<<"Enter the string\n";
	//cin>>text;
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
				l[j].freqi+=1;
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
			l[ToTSize].var = text[i];
			l[ToTSize].freqi = 1;
			n[endd].freq=1;
			n[endd].lcptr=NULL;
			n[endd].rcptr=NULL;
			ToTSize++;
			for(int j=0;j<100;j++)
				n[endd].encode[j]=-666;
			
		}
	}
	for(int i=0;i<=endd;i++)
	{
		cout<<n[i].c<<"-->"<<n[i].freq<<endl;
	}
	cout<<"INPUT IS DONE ABOVE\n";
}

//******************************************

void Huffman::Huffmantree()
{
	while(endd-beg>0)
	{
		sort(n+beg,n+(endd+1),freqsort);   // Sorted in desc. order
		endd++;
		n[endd].freq=n[beg].freq+n[beg+1].freq;
		n[endd].c='\0';
		n[endd].lcptr=&n[beg];
		n[endd].rcptr=&n[beg+1];
		for(int i=0;i<100;i++)
			n[endd].encode[i]=-666;
				
		beg+=2;
	}
	
	hptr=&n[beg];	
}

//******************************************

void Huffman::code(struct node *ptr,int arr[],int top)
{
	if(ptr->lcptr)
	{	arr[top]=0;
		code(ptr->lcptr,arr,top+1);
	}
	
	if(ptr->rcptr)
	{
		arr[top]=1;
		code(ptr->rcptr,arr,top+1);
	}
	
	if(ptr->lcptr==NULL && ptr->rcptr==NULL)
	{
		for(int i=0;i<top;i++)
			ptr->encode[i]=arr[i];		
	}
}

//******************************************

void Huffman::encodeInput()
{
	int i=0,k=0;
	for(int i=0;i<1000;i++)
	{
		eInput[i]=-666;
		eIn[i]=-666;
	}
		
	cout<<"The Encoded form for given input ==> "<<text<<" ==> is \n";
	while(i<text.length())
	{
		for(int j=0;j<10;j++)
			if(dict[text[i]][j]!=-666)
			{
				cout<<dict[text[i]][j];
				eInput[k]=dict[text[i]][j];
				eIn[k]=dict[text[i]][j];
				k++;
			}
		i++;
	}
	//cout<<"\nYOLO\n";
	/*for(int i=0;i<1000;i++)
		cout<<eIn[i];
	cout<<"\nYOLO2\n";*/
	//cout<<endl;
	eTTop=k;
}

//******************************************

void Huffman::decode(struct node *ptr)
{
	for(int i=0;i<eTTop;i++)
	{
		if(eInput[i]==0)
		{
			ptr=ptr->lcptr;
		}
		else
		{
			ptr=ptr->rcptr;
		}
		if(ptr->lcptr==NULL && ptr->rcptr==NULL)
		{
			cout<<ptr->c;
			ptr=hptr;
		}
	}
}


//******************************************
int pos=0;
void print(struct node *ptr)
{
	if(ptr!=NULL)
	{
		print(ptr->lcptr);
		//l[pos].var = ptr->c;
		cout<<ptr->c<<"-->"<<ptr->freq;
		cout<<" ENCODE :";
		for(int i=0;i<100;i++)
		{
			dict[ptr->c][i]=ptr->encode[i];
			if(ptr->encode[i]!=-666)
			{
				cout<<ptr->encode[i];
				//l[pos].EN[i]=ptr->encode[i];
			}
		}
		pos++;		
		cout<<endl;
		print(ptr->rcptr);
	}
}
//******************************************

void look()
{
	for(int i=0;i<128;i++)
	{
		for(int j=0;j<10;j++)
		if(dict[i][j]!=-666)
			cout<<dict[i][j];
		cout<<" ";
	}
	cout<<endl;
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
	client.sin_addr.s_addr =INADDR_ANY;	// if any IP is connecting with this IP for that we are using INADDR_ANY
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


