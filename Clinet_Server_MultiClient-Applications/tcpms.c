#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
 #include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
int s_sock,c_client;
char buf[100];
int flag=0;
pid_t childpid;       //pid_t data type defines within the types.h header file(it create a childpid for multitasking operation"
socklen_t addr_size;
s_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,other;
memset(&server,0,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(4442); // port is the point of communication between the client and server
server.sin_addr.s_addr=INADDR_ANY; // Any address means server can host to any client with valid IP


if(bind(s_sock,(struct sockaddr*)&server,sizeof(server))==-1)
{
printf("[+] bind error\n");
exit(1);
}
printf("[+] server is bind%d\n",4442);
if(listen(s_sock,10)==0)
printf("[+] sever listing...\n");
while(1) // infinte loop needed to accept the mutliclient connection to a server
{
    c_client=accept(s_sock,(struct sockaddr*)&other,&addr_size);
    if(c_client==-1)
      exit(1);
     // print the address and port umber of client connections
    childpid=fork();
    if(childpid==0)  // child thread creation (if it return zero then terminate the connection or close the socket)
    {
       char *s = inet_ntoa(other.sin_addr);
       printf("[+] conection accepted from %s,%d\n",s,ntohs(other.sin_port));
        close(s_sock);
        while(1) // this infinte loop for maintining the client-server message exchage
        {
            recv(c_client,buf,sizeof(buf),0);
            if((strncmp(buf,"end",3)==0) || (strncmp(buf,"\0",1)==0))          //if message from client "end" terminate the client socket
            {
                break;
            }
            printf("client msg:%s \t PPID=%d\tPID=%d\n",buf,getppid(),getpid());
            //fflush(stdout);
            send(c_client,buf,sizeof(buf),0);
            bzero(buf,sizeof(buf)); //clear the buffer every time to receive the new messages (otherwise override will give addtional past stored message)
        }
        //printf("[+] conection Disconnected from %s,%d\n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
        // if(flag==1)
        //     break;
    }
    
}
close(s_sock);
return 0;
}
