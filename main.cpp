#include <iostream>

#include "client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    Client* client = new Client();
    Client::Command command;
    if(client->start_client() < 0) return -1;
    if(client->connect_to_server()< 0) return -1;
    if(client->send_command(command)) return -1;
    client->close_socket();
    delete client;
    return 0;
}

