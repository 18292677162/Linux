#include "ChatClient.hpp"

udp_client::udp_client(std::string _remote_ip, unsigned short _remote_port)
    :remote_ip(_remote_port), remote_ port(_remote_port), sock(-1)
{
}

int udp_client::init_client()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("sock")
        exit(1);
    }
    return 0;
}




                                                                            
