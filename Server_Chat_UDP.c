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
		printf("Usage: %s <port_no>\n", argv[0]);
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
	socklen_t lenr = sizeof(rmaddr);
	socklen_t len = sizeof(saddr);
	
	//1. Bind is used for assigning port
	 if (bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) 
	{
		perror("bind");
		close(sfd);
		exit(3);
	} 
	 
	
	
// To make a program for chatting
	
	while(1){
		char rcbuf[50] = {0}, trbuf[50] = {0}, ch;
		int ret = 0;
		if ((ret = recvfrom(sfd, rcbuf, sizeof(rcbuf), 0, (struct sockaddr *)&rmaddr, &lenr)) < 0)
		{
			perror("recvfrom");
			//close(cfd);
			close(sfd);
			exit(6);
		}
		
		printf("%s of length = %d\n", rcbuf, ret);
		
		int i =0;
		while((ch = getchar())!= '\n'){
			trbuf[i] = ch;
			i++;
		}
		trbuf[i] = '\0';

		if (sendto(sfd, trbuf, ret, 0, (struct sockaddr *)&rmaddr, lenr) < 0)
		{
			perror("sendto");
			//close(cfd);
			close(sfd);
			exit(7);
		}
		memset(trbuf, 0, 50);
		memset(rcbuf, 0, 50);
	}

	//close(cfd);
	close(sfd);

	return 0;
}
