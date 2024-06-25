#include <iostream>

#include "client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    Client* client = new Client();
    Client::Command command;
    Client::Time_server time_s;
    if(client->start_client() < 0){
        delete client;
        return -1;
    }
    if(client->connect_to_server()< 0){
        delete client;
        return -1;
    }
    while(true){

        std::cout << "введите команду" << std::endl;
        std::cin >> command.command_type;

        if(client->send_command(command) < 0){
            delete client;
            return -1;
        }

        if(command.command_type == 1){
            if(client->recv_time(time_s) < 0){
                delete client;
                return -1;
            }
            tm* timeinfo = localtime(&time_s.seconds);
            std::cout << "Время на сервере - " << asctime(timeinfo) << std::endl;
        }

        if(command.command_type == 2){
            return 0;
        }
    }

    client->close_socket();
    delete client;
    return 0;
}

