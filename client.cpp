#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

const int port = 6666;
const char* ip = "192.168.31.98";

int main()
{
    int socketId;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    socklen_t addr_len = sizeof(addr);
    if (connect(socketId, (struct sockaddr*)&addr, addr_len) < 0)
    {
        perror("connect");
        return 2;
    }

    char ch[2];
    ch[1] = '\n';
    system("stty -icanon");
    while (true)
    {
        ch[0] = getchar();
        if (write(socketId, &ch, 2) <= 0)
            break ;
    }

    close(socketId);

    return 0;
}
