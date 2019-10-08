#include <stdio.h>
#include <time.h>
 
int loop(int i) 
{
    time_t start, end;
    double elapsed;
 	int k=0;
 	int a=0;
    time(&start);  /* start the timer */
 
    do 
    {
    	//printf("%d\n",a );
        time(&end);
 
        elapsed = difftime(end, start);
        /* For most data types one could simply use
            elapsed = end - start;
            but for time_t one needs to use difftime(). */
 		if(elapsed==k)
 		{
 			printf("elapsed %f\n", elapsed);
 			k++;
 		}
 		printf("HIII\n");
 		

    } while(elapsed < i);  /* run for ten seconds */

 return 0;
}

int main()
{
	int x=3;
	for(int i=0;i<2;i++)
	while(loop(x))
		
	return 0;
}

//how to run a timer process in background and a scanf function in forground in c
// Bring a bg proocess to fg
// how to bring Ctrl+Z ./a.out to resumption
// Where can i find the c code for linux executables
// Can i edit the kernel src code. if so where can i find it,