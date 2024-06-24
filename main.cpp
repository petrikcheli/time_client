#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_server < 0){
        std::cerr << "Ошибка создания сокета" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = 6666;

    if (inet_pton(AF_INET, "192.168.31.45",
                  &(server_addr.sin_addr)) <= 0){
        std::cerr << "Неверный IP адрес" << std::endl;
        exit(1);
    }


    if(connect(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr))< 0){
        std::cerr << "Не удалось подключиться к серверу" << std::endl;
        return -1;
    }

    struct Command{
        int command_type;
    }command;

    std::cin >> command.command_type;

    if(send(socket_server, &command, sizeof(command), 0) < 0){
        std::cerr << "не удалось отправить команду серверу" << std::endl;
        return -1;
    }

    shutdown(socket_server, 2);

    if(socket_server != -1){
        close(socket_server);
        socket_server = -1;
    }

    return 0;
}
