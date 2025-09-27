// echo_client.cpp
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    string msg;
    char buf[1024];

    while (getline(cin, msg)) {
        if (msg == "exit") break;
        send(sock, msg.c_str(), msg.size(), 0);
        int n = recv(sock, buf, sizeof(buf), 0);
        cout << "Echo: " << string(buf, n) << endl;
    }

    close(sock);
    return 0;
}
