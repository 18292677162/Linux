#include <iostream>
#include <poll.h>
#include <unistd.h>

int main()
{
    struct pollfd fd_set;
    fd_set.fd = 0;
    fd_set.events = POLLIN;
    fd_set.revents = 0;
    
    for(;;){
        switch(poll(&fd_set, 1, 1000)){
            case -1:
                std::cerr << "Poll Error!" << std::endl;
                break;
            case 0:
                std::cout << "Poll timeout..." << std::endl;
                break;
        }
        if(fd_set.revents == POLLIN){
            char buf[1024] = {0};
            read(0, buf, sizeof(buf) - 1);
            std::cout << "std_in: " << buf;
        }
    }
    return 0;
}
