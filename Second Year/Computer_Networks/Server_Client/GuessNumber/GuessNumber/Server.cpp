#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <winsock2.h>
#include<cstdint>
#pragma comment(lib,"Ws2_32.lib")
#include <stdio.h>
#include <thread>
#include <iostream>

using namespace std;


int client_count = 0;
int start = 1;
int stop = pow(2,17) - 1;
float my_nr = (float)(rand()) / (float)(rand());

int worker(int cs) {
	int my_idcount = client_count;
	cout << "Client #" << client_count;
	string msg = "Hello client! You are entering the number guess competion now";
	int res = send(cs, (char*)&msg, sizeof(msg), 0);
	float  number;
	res = recv(cs, (char*)&number, sizeof(number), 0);

	return 1;
}

int main() {

	struct sockaddr_in server, client;
	int rs = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(rs, (struct sockaddr*)&server, sizeof(server)) < 0) {
		perror("Bind error:");
		return 1;

	}
	listen(rs, 5);
	int l = sizeof(client);

	while (true) {
		int cs = accept(rs, (struct sockaddr*)&client, &l);

		std::thread my_thr(worker, cs);
		client_count++;
	}
}