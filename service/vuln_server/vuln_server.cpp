// vuln_server.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

char *do_server(SOCKET client)
{
	char temp[128];
	int length;

	sprintf(temp, "Hello!\n");
    send(client,temp,strlen(temp),0);

	length = recv(client, temp, 10000, 0);
	printf("Received %d (%x) bytes...\n", length, length);
	

    return temp;
}

int main(int argc, char *argv[])
{
	int length;

	SOCKET server;
	WSADATA wsaData;
	sockaddr_in local;
	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);

	int wsaret = WSAStartup(0x101,&wsaData);

	if(wsaret!=0)
		return 0;

	//Now we populate the sockaddr_in structure
	local.sin_family = AF_INET; //Address family
	local.sin_addr.s_addr = INADDR_ANY; //Wild card IP address
	local.sin_port=htons(12345); //port to use

	//the socket function creates our SOCKET
	server=socket(AF_INET,SOCK_STREAM,0);

	//If the socket() function fails we exit
	if(server==INVALID_SOCKET)
		return 0;

	//bind links the socket we just created with the sockaddr_in 
	//structure. Basically it connects the socket with 
	//the local address and a specified port.
	//If it returns non-zero quit, as this indicates error
	if(bind(server,(sockaddr*)&local,sizeof(local))!=0)
		return 0;

	//listen instructs the socket to listen for incoming 
	//connections from clients. The second arg is the backlog
	if(listen(server,10)!=0)
		return 0;

	for(;;)
	{
		client = accept(server, (struct sockaddr*)&from,&fromlen);

		do_server(client);
	    closesocket(client);
	}

    closesocket(server);
    WSACleanup();

	MessageBox(0, "hi", 0, 0);

	return 0;
}

