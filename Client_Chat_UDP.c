#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	if (argc < 3)
	{	// using command line argument
		printf("Usage: %s <serv_ip> <serv_port>\n", argv[0]);
		exit(1);
	}

	int cfd, serv_port;
	serv_port = strtoul(argv[2], NULL, 10);//string to unsigned long

	/*
	Create your Socket do error checking
	Remember socket returns a socket descriptor
	SOCK_STREAM --->TCP
	or
	SOCK_DGRAM  --->UDP
	AF_INET ------->protocol/address family

	*/
	if ((cfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(2);
	}
	

	struct sockaddr_in saddr = {0};
	struct sockaddr_in rmaddr = {0};
	saddr.sin_family = AF_INET; // set to AF_INET
	saddr.sin_port = htons(serv_port); // Port number
	saddr.sin_addr.s_addr = inet_addr(argv[1]); // IP address eg "192.168.1.1"
	socklen_t lenr = sizeof(rmaddr);
	socklen_t len = sizeof(saddr);

	/*
	1. Connect to the server using proper API for connect
	2. Send data to connected server
	3. Receive data from connected server and print data received
	4. Close the connection
	*/
	
	if (connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
	{
		perror("connect");
		close(cfd);
		exit(3);
	}


	
	while(1){
		char rcbuf[50] = {0}, trbuf[50] = {0}, ch;
		int i =0;
		while((ch = getchar())!= '\n'){
			trbuf[i] = ch;
			i++;
		}
		trbuf[i] = '\0';
		if (sendto(cfd, trbuf, strlen(trbuf), 0, (struct sockaddr *)&saddr, len) < 0)
		{
			perror("sendto");
			close(cfd);
			exit(4);
		}

		if (recvfrom(cfd, rcbuf, sizeof(rcbuf), 0, (struct sockaddr *)&saddr, &len) < 0)
		{
			perror("recvfrom");
			close(cfd);
			exit(5);
		}
		printf("%s\n", rcbuf);
		//memset(&rmaddr, 0, lenr);
		memset(rcbuf, 0, 50);
		memset(trbuf, 0, 50);
	}


	close(cfd); 

	return 0;
}
