/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：tcp_process.cpp
*   创 建 者：Angela
*   创建日期：2020年06月25日
*   描    述：
*
================================================================*/

#include "tcp_svr.hpp"
#include <sys/wait.h>

#define CHECK_RET(p) if(p == false) {return -1;}

void sigcb(int signo)
{
    (void)signo;
    waitpid(-1, NULL, 0);
}

int main()
{
    signal(SIGCHLD, sigcb);

    TcpSvr listen_ts;
    CHECK_RET(listen_ts.CreateSocket());
    CHECK_RET(listen_ts.Bind("172.16.99.129", 19999));
    CHECK_RET(listen_ts.Listen());

    TcpSvr newts;
    while(1)
    {
        struct sockaddr_in cli_addr;
        CHECK_RET(listen_ts.Accept(&newts, &cli_addr));

        printf("Hava a new connect [%s][%d]\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

        int pid = fork();
        if(pid < 0)
        {
            perror("fork");
            return 0;
        }
        else if(pid == 0)
        {
            //child
            while(1)
            {
                std::string buf;
                newts.Recv(&buf);
                printf("Client tell me [%s]\n", buf.c_str());

                printf("send client data: ");
                fflush(stdout);
                buf.clear();
                std::cin >> buf;

                newts.Send(buf);
            }
            newts.Close();
            exit(1);
        }

        //大于0， 父进程逻辑
        newts.Close();
    }
    return 0;
}
