#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<math.h>

int main()
{
	int Mes[100];
	int m;
	int r;
	printf("Enter the number of bits of Message\n");    //1 1 0 | 0
	scanf("%d",&m);
	printf("Enter the data\n");
	for(int i=0;i<m;i++)
		scanf("%d",Mes[i]);

	int k;
	for(k=1;;k++)
		if(pow(2,k) >= m+k+1)
			break;

	// NOW I HAVE m and k Create the

	int Data[m+k+1];
	for(int i=1;i<m+k+1;i++)

	return 0;
}