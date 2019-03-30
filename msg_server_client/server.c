#include "comm.h"

int main()
{
    int msgid = createMsgQueue();

    char buf[1024];
    while(1){
        buf[0] = 0;
        recvMsg(msgid, CLIENT_TYPE, buf);
        printf("client say# %s\n", buf);

        printf("Please Enter# ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf));
        if(s > 0){
            buf[s-1] = 0;
            sendMsg(msgid, SERVER_TYPE, buf);
            printf("send done, wait recv...\n");
        }
    }
    destroyMsgQueue(msgid);
    return 0;
}
