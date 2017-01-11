#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")

#define BUFF_SIZE 1024

int connect_page(char * save)
{
	WSADATA wsa;
	int lenght;

	struct hostent *host;
	char Type_header[BUFF_SIZE];
	char save_header[BUFF_SIZE];
	char result[BUFF_SIZE] = { 0, };

	char *url[1] = { save };

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

	host = gethostbyname(url[0]);

	if (host == NULL)
	{
		printf("Url Fail ! \n");
		return 0;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));

	if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		printf("Not Connect \n");
		system("pause");
		return 1;
	}
	else
	{
		printf("!! Connect Success !!\n Type the http header : ");
		scanf("%s", Type_header);
		sprintf(save_header, "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", Type_header);
	}
	send(sock, save_header, strlen(save_header), 0);

	while (1)
	{
		if ((lenght = recv(sock, result, BUFF_SIZE - 1, 0)) <= 0)
		{
			break;
		}
		puts(result);
		memset(result, 0, BUFF_SIZE);
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}

int main()
{
	char site[BUFF_SIZE];

	printf("Type the Site : ");
	scanf("%s", site);

	connect_page(site);

	system("pause");

	return 0;
}