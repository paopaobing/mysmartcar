
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <netdb.h>
#include <errno.h>

#include "car.h"
#include "carmer.h"

const int port = 6666;
const char* ip = "0.0.0.0";

Car car;
Carmer carmer;

void handle(int socketId)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));

    fd_set rdfs;
    struct timeval tv;

    while (true)
    {
        tv.tv_sec = 0;
        tv.tv_usec = 300000;
        FD_ZERO(&rdfs);
        FD_SET(socketId, &rdfs);
        switch (select(socketId+1, &rdfs, NULL, NULL, &tv))
        {
            case -1:
                return ;
            case 0:
                car.stop();
                break ;
            default :
            {
                if (FD_ISSET(socketId, &rdfs))
                {
                    int size;
                    if ((size = read(socketId, buf, 10)) <= 0)
                        return ;
                    for (int i = 0; i < size; i ++)
                    {
                        switch (buf[i])
                        {
                            case 'w': car.run();       break ;
                            case 's': car.back();      break ;
                            case 'a': car.left();      break ;
                            case 'd': car.right();     break ;
                            case 'e': car.turn_right();break ;
                            case 'q': car.turn_left(); break ;
                            case ' ': car.stop();      break ;
                            case 'i': carmer.Up();     break ;
                            case 'k': carmer.Down();   break ;
                            default :                  break ;
                        }
                    }
                }
            }
        }
    }
}



int main()
{
    int socketId;
    if ((socketId = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }

    //设置端口可复用
    int opt = 1;
    setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    if (bind(socketId, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return 2;
    }

    int listen_sock = listen(socketId, 5);
    if (listen_sock < 0)
    {
        perror("listen");
        return 3;
    }

    wiringPiSetup();
    car.Init();
    carmer.Init();

    struct sockaddr_in peer;
    socklen_t peer_len;
    char buf[1024];
    do
    {
        int accept_fd = accept(socketId, (struct sockaddr*)&peer, &peer_len);
        if (accept_fd < 0)
        {
            perror("accept");
            continue ;
        }

        printf("connected with ip: %s  and port: %d\n", inet_ntop(AF_INET,&peer.sin_addr, buf, 1024), ntohs(peer.sin_port));

        handle(accept_fd);

        car.stop();
    } while (true);

    close(socketId);

    return 0;
}
