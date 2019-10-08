#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
using namespace std;

//******************************************
struct node
{
	char c;
	int freq;
	struct node *lcptr;
	struct node *rcptr;
	int encode[10];
	
}n[10],*hptr;

//******************************************

int endd=-1;
int beg=-1;
int dict[128][10];
int eTTop=0;


//*******    FREQSORT   *********************
bool freqsort(node n1,node n2)
{
	return (n1.freq < n2.freq);
}

//*********   Class  ***********************
class Huffman
{
	private:
		char text[100];
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
	cin>>text;
	int chk=0;
	for(int i=0;i<strlen(text);i++)
	{
		chk=0;
		for(int j=0;j<=endd;j++)
		{
			if(n[j].c==text[i])
			{
				n[j].freq+=1;
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
			n[endd].freq=1;
			n[endd].lcptr=NULL;
			n[endd].rcptr=NULL;
			for(int k=0;k<10;k++)
				for(int j=0;j<10;j++)
					n[k].encode[j]=-666;
			
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
		for(int i=0;i<10;i++)
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
		eInput[i]=-666;
		
	cout<<"The Encoded form for given input "<<text<<" is ";
	while(i<strlen(text))
	{
		for(int j=0;j<10;j++)
			if(dict[text[i]][j]!=-666)
			{
				cout<<dict[text[i]][j];
				eInput[k]=dict[text[i]][j];
				k++;
			}
		i++;
	}
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

void print(struct node *ptr)
{
	if(ptr!=NULL)
	{
		print(ptr->lcptr);
		cout<<ptr->c<<"-->"<<ptr->freq;
		cout<<" ENCODE :";
		for(int i=0;i<10;i++)
		{
			dict[ptr->c][i]=ptr->encode[i];
			if(ptr->encode[i]!=-666)
				cout<<ptr->encode[i];
		}
				
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
	cout<<"------------------\n";
	/*cout<<endl;
	
	for(int i=0;i<1000;i++)
	{
		if(h.eInput[i]!=-666)
		cout<<h.eInput[i];
	}
	*/
	cout<<"\nThe Decoded format for the given input is ";
	h.decode(hptr);
	
	cout<<endl;
}


