#include<stdio.h>
#include <math.h>
int main()
{
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
	printf("KEY ARRAY\n");
	for(int i=keysize-1;i>=0;i--)
		printf("%d ", key[i]);
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
	printf("\nDATA ARRAY\n");
	for(int i=totsize-1;i>=0;i--)
		printf("%d ", data[i]);
	int data_copy[100];
	printf("TOT SIZE %d\n",totsize-1 );
	for(int i=totsize-1;i>=0;i--)
		data_copy[i] = data[i];

	int Quo;
	int count=0;
	int k=totsize-1;
	int init=0;
	while(k>=keysize-1)
	{ 
		count=0;
		printf("%d\n",k );
		for(int i=k,j=keysize-1;i>=0,j>=0;i--,j--)
		{
			printf("DATA _ %d %d\n",data_copy[i],i);
			printf("KEY _ %d %d\n",key[j],j);
			if(data_copy[i]==0 && key[j]==1 && init==0)
			{}
			else
			{	data_copy[i] = data_copy[i] ^ key[j];
				init=1;
			}
			printf("\n%d\n",data_copy[i]);
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
	}
	printf("\nFinal answer\n");
	for(int i=totsize-1;i>=0;i--)
		printf("%d ",data[i]);
	printf("\n");

return 0;
}