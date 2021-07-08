#include <iostream>
#pragma comment(lib, "ws2_32.lib") //доступ до функцій
#include <winsock2.h> //бібліотека для роботи з сокетами
#pragma warning(disable: 4996);
using namespace std;

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1); //версія бібліотеки winsock2
	if (WSAStartup(DLLVersion, &wsaData) != 0) //для загрузки бібліотеки // при успілгній загрузці - функція поверне 0!
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
	//cout << addr.sin_port << endl;
	SOCKET sList = socket(AF_INET, SOCK_DGRAM, NULL); //створення сокет (сімейство прококолів, тип протоколів, протокол (0-по умол) )

	//привязка адресу сокету - bind
	bind(sList, (SOCKADDR*)&addr, sizeof(addr)); // (попередньо створений сокет, вказівник на структуру SOCKADDR, розмір структури)
	//listen(sList, SOMAXCONN);  // для зєднання з клієнтом (сокет, максимальна кількість запитів)

	int sizeaddr = sizeof(addr);
	int client_len = sizeof(addr);

	//Do-While Loop to recieve data
	char buf[512];

	while (true)
	{

		//Wait for the message

		int bytesRecieved = recvfrom(sList, buf, 512, 0, (struct sockaddr*)&addr, &sizeaddr);
		if (bytesRecieved == SOCKET_ERROR)
		{
			cerr << "Error recieving from client" << WSAGetLastError() << endl;
			continue;
		}

		cerr << "Msg from client $ " << buf << endl;

	}

	//Shutdown the connection
	cin.get();
	closesocket(sList);
	WSACleanup();
	return 0;
}

