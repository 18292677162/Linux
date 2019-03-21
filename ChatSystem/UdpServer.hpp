#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "comm.h"
#include "data_pool.h"
#include "udp_data.h"

using namespace std;

class udp_server
{
    public:
        udp_server(unsigned short _port = 8080);
        int init_server();
        int reliable_recv_msg();
        int reliable_send_msg(const std::string &_in_msg, const struct sockaddr_in &client, socklen_t len);
        int broadcast_msg();
        ~udp_server();
    private:
        int recv_msg(std::string &_out_msg);
        int send_msg(const std::string &_in_msg, const struct sockaddr_in &client, socklen_t len);
        bool register_user(const struct sockaddr_in &client, std::string&);
    private:
        int sock;
        unsigned short port;
}
