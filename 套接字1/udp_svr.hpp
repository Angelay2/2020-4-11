#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

class UdpSvr
{
    public:
        UdpSvr()
        {
            sockfd_ = -1;
        }

        ~UdpSvr()
        {

        }

        bool CreateSock()
        {
            sockfd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
            //1.将点分十进制的ip地址转换成为uint32整数
            //2.将主机字节序转换成为网络字节序
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = bind(sockfd_, (struct sockaddr*)&addr, sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }

        bool Send(std::string& data, struct sockaddr_in* dest_addr)
        {
            int send_size = sendto(sockfd_, data.c_str(), data.size(), 0, (struct sockaddr*)dest_addr, sizeof(struct sockaddr_in));
            if(send_size < 0)
            {
                perror("sendto");
                return false;
            }
            return true;
        }

        bool Recv(std::string* data, struct sockaddr_in* src_addr = NULL)
        {
            char buf[1024] = {0};
            ssize_t recv_size = -1;
            if(!src_addr)
            {
                 recv_size = recvfrom(sockfd_, buf, sizeof(buf) - 1, 0, NULL, NULL);
            }
            else
            {
                socklen_t addrlen = sizeof(struct sockaddr_in);
                recv_size = recvfrom(sockfd_, buf, sizeof(buf) - 1, 0, (struct sockaddr*)src_addr, &addrlen);

            }
            if(recv_size < 0)
            {
                perror("recvfrom");
                return false;
            }

            data->assign(buf, recv_size);
            return true;
        }

        void Close()
        {
            close(sockfd_);
            sockfd_ = -1;
        }
    private:
        int sockfd_;
};
