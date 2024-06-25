#ifndef CLIENT_H
#define CLIENT_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client
{
    int PORT_SERVER = 8080;
    const char* IP_SERVER = "192.168.31.142";
    int socket_server;
    struct sockaddr_in server_addr{};
public:
    struct Command{
        int command_type = 0;
    };

    Client();
    ~Client();
    int start_client();
    int connect_to_server();
    int send_command(struct Command& command);
    int recv_command(struct Command& command);
    int close_socket();
};

#endif // CLIENT_H
