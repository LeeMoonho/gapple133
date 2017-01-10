#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")

#define BUFF_SIZE 1024

int main()
{
	WSADATA wsa;
	struct hostent *host;
	char msg[BUFF_SIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		perror("WSAStart Error ");
		system("pause");
		return -1;
	}

	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;

	if (sock == INVALID_SOCKET)
	{
		perror("Sock Error ");
		system("pause");
		return -1;
	}
	host = gethostbyname("www.google.co.kr");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));

	if(connect(sock,(SOCKADDR*)&addr,sizeof(addr)) == SOCKET_ERROR) 
	{
		printf("Not Connect \n");
		system("pause");
		return 1;
	}
	send(sock, "GET / HTTP/1.1\r\nHost: www.google.co.kr\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: www.google.co.kr\r\n\r\n"), 0);
	recv(sock,msg,BUFF_SIZE,0);

	printf("%s \n",msg);

	closesocket(sock);
	WSACleanup();
	system("pause");
	
	return 0;
}
