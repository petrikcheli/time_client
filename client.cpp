#include "client.h"
#include <iostream>
Client::Client() {}
Client::~Client() {}

int Client::start_client(){
    socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server < 0){
        std::cerr << "Ошибка создания сокета" << std::endl;
        return -1;
    }


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = 8080;

    if (inet_pton(AF_INET, IP_SERVER,
                  &(server_addr.sin_addr)) <= 0){
        std::cerr << "Неверный IP адрес" << std::endl;
        return -1;
    }



    return 0;
}

int Client::connect_to_server(){
    if(connect(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        std::cerr << "Не удалось поключиться к серверу" << std::endl;
        return -1;
    }

    return 0;
}

int Client::send_command(struct Command& command){
    std::cout << "введите команду" << std::endl;
    std::cin >> command.command_type;
    if(send(socket_server,  &command, sizeof(command), 0) < 0){
        std::cerr << "Не удалось отправить команду серверу" << std::endl;
        return -1;
    }
    return 0;
}

int Client::recv_command(struct Command& command){
    if(recv(socket_server, &command, sizeof(command), 0) < 0){
        std::cerr << "Не удалось принять команду от сервера" << std::endl;
        return -1;
    }
    return 0;
}

int Client::close_socket(){
    shutdown(socket_server,2);
    if(socket_server != 0){
        close(socket_server);
        socket_server = -1;
    }
    return 0;
}

