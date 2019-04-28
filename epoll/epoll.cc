#include <iostream>
#include <sys/epoll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/

int StartUp(int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){

    }

    listen(sock, 5);

    return sock;
}

void EpollEventsAdd(int epfd, int listen_sock, uint32_t event)
{
    struct epoll_event ev;
    ev.events = event;
    ev.data.fd = sock;
    eopll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
}

void EpollEventsDel(int epfd, int sock)
{
    epoll_ctl()
}

void EpollEventsEx
{
    struct epoll_event ev;
    ev.event = event;
    ev.data.fd = sock;
    epoll_ctl(epfd ,EPOLL_CTL_MOD, sock ,&ev);

}


void HandlerEvents(int epfd, struct epoll_event revs[],int num, int listen_sock)
{
    for(auto i = 0;i < num; i++){
        uint32_t revent = revs[i].events;
        int fd = revs[i].data.fd;
        if(revent & EPOLLIN){
            if(fd == listen_sock){
                //accept
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                int sock = accept(fd, (struct sockaddr*)&peer, &len);
                if(sock < 0){
                    std::cerr << "accept error!" << std::endl;
                    continue;
                }
                EpollEventsAdd(epfd, sock ,EPOLLIN);
            }
            else{
            //read
            char buf[10240];
            ssize_t s = recv(fd, buf, sizeof(buf)-1, 0);
            if(s > 0){
                buf[s] = 0;
                std::cout << "###############" << std::endl;
                std::cout << buf << std::endl;
                std::cout << "###############" << std::endl;

                EpollEventsEx(epfd ,fd,event);
            }else if(s == 0){
                EpollEventsDel(epfd, fd);
                close(fd);
            }else{
                EpollEventsDel(epfd, fd);
                close(fd);
            }
        }
        }
        else if(event & EPOLLOUT){
            //write
            std::string echo_http = "HTTP/1.0 200 OK\r\n\r\n<html><h3>hello epoll!</h3></html>"
        }
    }
}

int main()
{
    int listen_sock = StartUp();
    int epfd = epoll_create(256);
    if(epfd < 0){
        std::cerr << "epoll error" << std::endl;
        exit(3);
    }

    EpollEventsAdd(epfd, listen_sock, EPOLLIN);
    struct epoll_event revs[64];
    while(1){
        int timeout = 1000;
        int num = epoll_wait(epfd, revs, 64, timeout);
        switch(num){
            case -1:
                std::cout << "eopll error" << endl;
                break;
            case 0:
                std::cout << "time out..." << endl;
                break;
            default:
                HandlerEvents(spfd, revs, num, listen_sock);
        }
    }

    return 0;
}
