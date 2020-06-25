/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：tcp_svr.cpp
*   创 建 者：Angela
*   创建日期：2020年06月25日
*   描    述：
*
================================================================*/


#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

class TcpSvr
{
    public:
        TcpSvr()
        {
            sockfd_ = -1;
        }

        ~TcpSvr()
        {

        }

        bool CreateSocket()
        {
            sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(sockfd_ < 0)
            {
                perror("socket");
                return false;
            }
            return true;
        }

        bool Bind(const std::string& ip, uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = bind(sockfd_, (struct sockaddr*)&addr, sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Listen(int backlog = 5)
        {
            int ret = listen(sockfd_, backlog);
            if(ret < 0)
            {
                perror("listen");
                return false;
            }
            return true;
        }

        bool Accept(TcpSvr* newts, struct sockaddr_in* peeraddr)
        {
            //accept函数的第一个参数是侦听套接字
            //返回值是新创建出来的套接字
            socklen_t addrlen = sizeof(struct sockaddr_in);
            int newfd = accept(sockfd_, (struct sockaddr*)peeraddr, &addrlen);
            if(newfd < 0)
            {
                perror("accept");
                return false;
            }
            newts->sockfd_ = newfd;
            return true;
        }

        bool Connect(const std::string& ip, uint16_t port)
        {
            struct sockaddr_in dest_addr;
            dest_addr.sin_family = AF_INET;
            dest_addr.sin_port = htons(port);
            dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = connect(sockfd_, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
            if(ret < 0)
            {
                perror("connect");
                return false;
            }
            return true;
        }

        bool Send(std::string& data)
        {
            int send_size = send(sockfd_, data.c_str(), data.size(), 0);
            if(send_size < 0)
            {
                perror("send");
                return false;
            }
            return true;
        }

        bool Recv(std::string* data)
        {
            char buf[1024] = {0};
            int recv_size = recv(sockfd_, buf, sizeof(buf) - 1, 0);
            if(recv_size < 0)
            {
                perror("recv");
                return false;
            }
            else if(recv_size == 0)
            {
                //对端关闭了连接
                printf("peer shutdown connect\n");
                return false;
            }
            data->assign(buf, recv_size);
            return true;
        }

        void Close()
        {
            close(sockfd_);
        }
    private:
        //套接字描述符
        //   有可能是侦听套接字
        //   有可能是新连接的套接字
        int sockfd_;
};



