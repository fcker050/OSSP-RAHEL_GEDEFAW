#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread> 

// Server code (as a function)
void server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server listening..." << std::endl;

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    std::cout << "Connection accepted" << std::endl;

    close(new_socket);
    close(server_fd);
}

// Client code (as a function)
void client() {
    sleep(1); 

    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr));

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    std::cout << "Client connected to server" << std::endl;

    close(sock);
}

int main() {
    // Create server thread
    std::thread server_thread(server);

    // Create client thread
    std::thread client_thread(client);

    server_thread.join();
    client_thread.join();

    return 0;
}

