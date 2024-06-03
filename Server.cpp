#include <stdio.h>
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
	//1. �T�{��ĳ����
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("��ĳ�������OV2.2!\n");
		//9. �M�z��ĳ�����T��
		WSACleanup();
		return -1;
	}
	printf("��ĳ������V2.2!\n");
	//2. �Ы�SOCKET
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		printf("�Ы�SOCKET����: %d\n", GetLastError());
		return -2;
	}
	printf("�Ы�SOCKET���\\n");
	//3. �T�wSERVER����ĳ�a�}
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;							//�PSOCKET��ƲĤ@�ӰѼƫO���@��
	//addr.sin_addr.S_un.S_addr = inet_pton("192.168.1.108"); //���aIP�a�}
	int status = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(10086);					//�j�p���ഫ  �b10000���k
	//4. �j�w
	int r = bind(sSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1) {
		printf("�j�w����: %d\n", GetLastError());
		//8. �_�}�s��
		closesocket(sSocket);
		//9. �M�z��ĳ�����T��
		WSACleanup();
	}
	printf("�j�w���\\n");
	//5. ��ť
	r = listen(sSocket, 10);
	if (r == -1) {
		printf("��ť����: %d\n", GetLastError());
		//8. �_�}�s��
		closesocket(sSocket);
		//9. �M�z��ĳ�����T��
		WSACleanup();
		return -2;
	}
	printf("��ť���\\n");
	//6. ���ݫȤ�ݳs��
	SOCKET cSocket = accept(sSocket, NULL, NULL);
	if (SOCKET_ERROR == cSocket) {
		printf("Server Crush: %d\n", GetLastError());
		//8. �_�}�s��
		closesocket(sSocket);
		//9. �M�z��ĳ�����T��
		WSACleanup();
		return -3;
	}
	printf("���Ȥ�ݳs�����\\n");
	//7. �q�T
	char buff[256] = { 0 };
	while (1)
	{
		r = recv(cSocket, buff, 255, NULL);  //�q�Ȥ�ݱ����ƾ�
		if (r > 0) {
			buff[r] = 0;   // �K�[�����Ÿ�
			printf(">>%s\n", buff);     // ��X
		}
	}
	while (1);
	return 0;
}