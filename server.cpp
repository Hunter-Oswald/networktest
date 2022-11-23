#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream>
#pragma comment(lib, "Ws2_32.lib")


int main() {
	std::ofstream ofs;

	//starts Winsock DLLs
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ofs << "ERROR: Failed to start WSA" << std::endl;
		return(1);
	}
	printf("Winsock DLLs started.\n");

	//create server socket
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		ofs << "ERROR: Failed to create ServerSocket" << std::endl;
		return(1);
	}
	printf("Server socket created.\n");

	//binds socket to address
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		ofs << "ERROR: Failed to bind ServerSocket" << std::endl;
		return(1);
	}
	printf("Server socket bound to address and configured.\n");

	//listen on a socket
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		ofs << "ERROR: listen failed to configure ServerSocket" << std::endl;
		return(1);
	}
	printf("Listening on ServerSocket.\n");

	//accepts a connection from a client
	SOCKET ConnectionSocket;
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return(1);
	}
	printf("Accepting connection from client...\n");

	// send and receive
	//recv(socket, data, length of data, 0)
	char received[12];
	recv(ConnectionSocket, received, 12, 0);
	printf("Receiving data from client...\n");
	printf(received);

	closesocket(ConnectionSocket); //closes incoming socket
	closesocket(ServerSocket); //closes server socket
	WSACleanup();

	return(0);
}