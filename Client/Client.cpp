#include <iostream>
#pragma comment(lib, "ws2_32.lib") //доступ до функцій
#include <winsock2.h> //бібліотека для роботи з сокетами
#pragma warning(disable: 4996);

using namespace std;

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); //версія бібліотеки winsock2
	if (WSAStartup(DLLVersion, &wsaData) != 0) //для загрузки бібліотеки // при успіншій загрузці - функція поверне 0!
	{
		cout << "error" << endl;
		exit(1);
	}
	/*else {
		cout << "OK";
	}*/

	//заповнення інформації про адрес сокета
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("192.168.0.110");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_DGRAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "ERROR" << endl;
	}

	string text;
	text = "Hello from client";
	send(Connection, text.c_str(), sizeof(text), NULL); //прийняти файл
}
