#include "udp_svr.hpp"

#define CHECK_RET(p) if(p == false){return 0;}

int main()
{
    UdpSvr us;
    CHECK_RET(us.CreateSock());
    CHECK_RET(us.Bind("172.16.99.129", 19999));

    while(1)
    {
        std::string buf;
        struct sockaddr_in peeraddr;
        us.Recv(&buf, &peeraddr);

        printf("Have a data [%s] form [%s]:[%d]\n", buf.c_str(), inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

        buf.clear();
        printf("reply response: ");
        fflush(stdout);
        std::cin >> buf;

        us.Send(buf, &peeraddr);
    }

    us.Close();
    return 0;
}
