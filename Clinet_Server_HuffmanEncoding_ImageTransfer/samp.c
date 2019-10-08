#include<stdio.h>
//#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//using namespace std;

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
int freqsort(struct node n1,struct node n2)
{
	return (n1.freq < n2.freq);
}

//*********   Class  ***********************
struct Huffman
{
	char text[100];
	int eInput[1000];
}h;

//*******   Func Defn. ********************

void read()
{
	printf("Enter the string\n");
	scanf("%s",h.text);
	int chk=0;
	for(int i=0;i<strlen(h.text);i++)
	{
		chk=0;
		for(int j=0;j<=endd;j++)
		{
			if(n[j].c==h.text[i])
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
			n[endd].c=h.text[i];
			n[endd].freq=1;
			n[endd].lcptr=NULL;
			n[endd].rcptr=NULL;
			for(int k=0;k<10;k++)
				for(int j=0;j<10;j++)
					n[k].encode[j]=-666;
			
		}
	}
	qsort(n,endd,sizeof(struct node),freqsort);
	for(int i=0;i<=endd;i++)
	{
		printf("%c --> %d\n", n[i].c,n[i].freq);
	}
	printf("INPUT IS DONE ABOVE\n");

}

//******************************************

void Huffmantree()
{
	//qsort(n,endd,sizeof(struct node),freqsort);  
	while(endd-beg>0)
	{
		qsort(n+beg,endd-beg+1,sizeof(struct node),freqsort);   // Sorted in desc. order
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

void code(struct node *ptr,int arr[],int top)
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

void encodeInput()
{
	int i=0,k=0;
	for(int i=0;i<1000;i++)
		h.eInput[i]=-666;
		
	printf("The Encoded form for given input %s is ",h.text);
	while(i<strlen(h.text))
	{
		for(int j=0;j<10;j++)
			if(dict[h.text[i]][j]!=-666)
			{
				printf("%d",dict[h.text[i]][j]);
				//cout<<dict[h.text[i]][j];
				h.eInput[k]=dict[h.text[i]][j];
				k++;
			}
		i++;
	}
	eTTop=k;
}

//******************************************

void decode(struct node *ptr)
{
	for(int i=0;i<eTTop;i++)
	{
		if(h.eInput[i]==0)
		{
			ptr=ptr->lcptr;
		}
		else
		{
			ptr=ptr->rcptr;
		}
		if(ptr->lcptr==NULL && ptr->rcptr==NULL)
		{
			printf("%c",ptr->c);
			//cout<<ptr->c;
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
		printf("%c --> %d\n",ptr->c,ptr->freq);
		//cout<<ptr->c<<"-->"<<ptr->freq;
		printf("ENCODE :");
		//cout<<" ENCODE :";
		for(int i=0;i<10;i++)
		{
			dict[ptr->c][i]=ptr->encode[i];
			if(ptr->encode[i]!=-666)
				printf("%d",ptr->encode[i]);
		}
				
		printf("\n");
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
			printf("%d",dict[i][j]);
		printf(" ");
	}
	printf("\n");
}

//*********  MAIN  *********************

int main()
{
	for(int i=0;i<128;i++)
	for(int j=0;j<10;j++)
	dict[i][j]=-666;

	int a[10];
	read();
	Huffmantree();
	code(hptr,a,0);
	print(hptr);
	//cout<<;
	printf("\n-----LOOKUP--------\n");
	look();
	printf("------Encoded Input--------\n");
	encodeInput();
	printf("------------------\n");
	/*cout<<endl;
	
	for(int i=0;i<1000;i++)
	{
		if(h.eInput[i]!=-666)
		cout<<h.eInput[i];
	}
	*/
	printf("\nThe Decoded format for the given input is ");
	decode(hptr);
	
	printf("\n");
}


