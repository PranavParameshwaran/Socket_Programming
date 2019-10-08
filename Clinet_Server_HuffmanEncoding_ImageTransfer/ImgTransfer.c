#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int c_socket;
	int Eof=0;
	char buff[100];
	c_socket = socket(AF_INET, SOCK_STREAM,0);		// AF_INET - consists all the ipv4 and ipv6 172.16.17.114
	struct sockaddr_in client;
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(9009);
	client.sin_addr.s_addr = INADDR_ANY; //inet_addr(IP);
	if(connect(c_socket,(struct sockaddr*)&client,sizeof(client)) == -1)
	{
		printf("Connection Issue\n");
		return 0;
	}

	FILE *fp;
	fp=fopen("Thresh_0.bmp","r"); // open a text file in read mode and store the file handle into fp
	/*int size;
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	fseek(fp,0,SEEK_SET);*/
	//write(c_socket,&size,sizeof(size));
	char endoffile = '0';
	char charbuf[1];
	while(!feof(fp))
	{
		charbuf[0]=fgetc(fp);
		//fread(buff,1,sizeof(buff),fp);
		//write(c_socket,buff,sizeof(buff));
		//bzero(buff,sizeof(buff));
		send(c_socket, &endoffile, sizeof(&endoffile), 0);
		send(c_socket, charbuf, sizeof(charbuf), 0);
	}

	printf("\n\n Image File Ended \n\n");
	endoffile = '1';
	send(c_socket, &endoffile, sizeof(&endoffile), 0);
	//Eof = 1;
	//send(c_socket,&Eof,sizeof(Eof),0);
	/*strcpy(buff,"Close");
	write(c_socket,buff,sizeof(buff));*/

	printf("File sent successfully\n");
	fclose(fp);
	close(c_socket);

	return 0;
}