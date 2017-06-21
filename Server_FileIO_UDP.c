#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <serv_port>\n", argv[0]);
		exit(1);
	}

	int sfd, cfd, port_no;
	port_no = strtoul(argv[1], NULL, 10);

		/*
	Create your Socket do error checking
	Remember socket returns a socket descriptor
	SOCK_STREAM --->TCP
	or
	SOCK_DGRAM  --->UDP
	AF_INET ------->protocol/address family

	*/
	 if ((sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	 {
		 perror("socket");
		 exit(2);
	 }

	struct sockaddr_in saddr = {0};
	struct sockaddr_in rmaddr = {0};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port_no);
	saddr.sin_addr.s_addr = INADDR_ANY;// Accept any ip address
	
	//1. Bind is used for assigning port
	 if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) 
	{
		perror("bind");
		close(sfd);
		exit(3);
	} 
	
 
	
// To make a program for file transfer
	char buf[100], cptr[2];
	int ret = 0, size = 0;
	socklen_t len = sizeof(rmaddr);
	
	ret = recvfrom(sfd, buf, 100, 0, (struct sockaddr *)&rmaddr, &len);
	if (ret  < 0)
	{
		perror("recvfrom");
		//close(cfd);
		close(sfd);
		exit(6);
	}
	
	FILE *fps = NULL;
	fps = fopen("samples.txt", "w");
	
	fwrite(buf, 1, ret, fps);

	close(cfd);
	close(sfd);

	return 0;
}
