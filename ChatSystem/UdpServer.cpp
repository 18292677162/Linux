#include "ChatServer.hpp"

udp_server::udp_server(unsigned short _port):port(_port)
{
    sock = -1;
}

static void print_log(std::string _log)
{
    std::cerr<<_log<<std::endl;
}

int udp_server::init_server()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0){
        perror("sock");
        exit(1);
    }
    
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);
    
    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        print_log(strerror(errno));
        exit(1);
    }
    return 0;
}

int udp_server::recv_msg(std::string &_out_msg)
{
    char buf[G_BLOCK_SIZE];
    memset(buf, '\0', sizeof(buf));
    socklen_t len = sizeof(client);
    struct sockaddr_in client;
    ssize_t _size = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&client, &len);
    if(_size < 0){
        print_log = " ";
        return 1;
    }else if(_size >= 0){
        _out_msg = buf;
        print_log(_out_msg);
        register_user(client, _out_msg);
    }
    return _size;
}

int udp_server::reliable_recv_msg()
{
    std::string _out_msg;
    int ret = recv_msg(_out_msg);
    if(ret > 0){
        print_log(_out_msg);
        pool.put_msg(_out_msg);
    }
    return ret;
}

bool udp_server::register_user(const struct sockaddr_in &client, std::string &_msg)
{
    std::string _ip_key = inet_ntoa(client.sin_addr);
    print_log(_ip_key);
    udp_data _data;
    _data.str_to_val(_msg);
    std::string _cmd;
    _data.get_cmd(_cmd);
    if(_cmd == "MESSAGE"){
        std::map<std::string, struct sockaddr_in>::iterator _iter = online_user.find(_ip_key);
        if(_iter != online_user.end()){
            return false;
        }
        online_user.insert(std::pair<std::string, struct sockaddr_in>(_ip_key, client));
        print_log("register done...");
    }else if(_cmd == "CMD-QUIT"){
        std::cout<<"Erase user: "<<_ip_key<<std::endl;
        online_user.erase(_ip_key);
    }
    return ture;
}

int udp_server::send_msg(const std::string &_in_msg, const struct sockaddr_in& client, socklen_t len)
{
    ssize_t _size = sendto(sock, _in_msg.c_str(), _in_msg.size(), 0, (struct sockaddr*)&client, len);
    if(_size < 0){
        print_log(strerror(errno));
        return 1;
    }else{}

    return 0;
}

int udp_server::broadcast_msg()
{
    std::string msg;
    pool.get_msg(msg);
    std::map<std::string, struct sockaddr_in>::iterator _iter = online_user.begin();
    for(; _iter != online_user.end(); _iter++ ){
        print_log("broadcast: ");
        print_log(msg);
        reliable_send_msg(msg, _iter->second, sizeof(_iter->second));
    }
}

int udp_server::reliable_send_msg(const std::string &_in_msg, const struct sockaddr_in &client, socklen_t len)
{
    return send_msg(_in_msg, client, len);
}

udp_server::~udp_server()
{
    if(sock != -1){
        close(sock);
    }
}
