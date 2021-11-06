#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include "../include/path.h"


void udp_msg_sender(int fd, struct sockaddr* dst)
{

    socklen_t len;
    struct sockaddr_un src;
    while(1)
    {
        char buf[512] = "TEST UDP MSG!\n";
        len = sizeof(struct sockaddr_un);
        printf("client:%s\n",buf);  //打印自己发送的信息
        sendto(fd, buf, sizeof(buf), 0, dst, len);
        memset(buf, 0, sizeof(buf));
        recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&src, &len);  //接收来自server的信息
        printf("server:%s\n",buf);
        sleep(1);  //一秒发送一次消息
    }
}

/*
    client:
            socket-->sendto-->revcfrom-->close
*/

int main(int argc, char* argv[])
{
    int client_fd;
    

    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    struct sockaddr_un ser_addr;

    ser_addr.sun_family = AF_UNIX;

    strcpy(ser_addr.sun_path, socket_path);
    

    udp_msg_sender(client_fd, (struct sockaddr*)&ser_addr);

    close(client_fd);

    return 0;
}