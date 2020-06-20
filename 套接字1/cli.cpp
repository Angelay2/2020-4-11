#include "udp_svr.hpp"

#define CHECK_RET(p) if(p == false) {return 0;}

int main()
{
    UdpSvr us;
    CHECK_RET(us.CreateSock());


    while(1)
    {
        printf("send dato to server: ");
        fflush(stdout);
        std::string buf;
        std::cin >> buf;

        //172.16.99.129 19999
        struct sockaddr_in dest_addr;
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(19999);
        dest_addr.sin_addr.s_addr = inet_addr("172.16.99.129");
        us.Send(buf, &dest_addr);

        buf.clear();
        us.Recv(&buf, NULL);
        printf("svrver tell me [%s]\n", buf.c_str());
    }
    us.Close();
    return 0;
}
