/*================================================================
*   Copyright (C) 2020 Sangfor Ltd. All rights reserved.
*   
*   文件名称：http_svr.cpp
*   创 建 者：Angela
*   创建日期：2020年06月27日
*   描    述：
*
================================================================*/

#include <string.h>
#include <sstream>

#include "tcp_svr.hpp"

#define CHECK_RET(p) if(p != true) {return 0;}


int main()
{
    TcpSvr ts;
    CHECK_RET(ts.CreateSocket());
    CHECK_RET(ts.Bind("192.168.119.131", 17778));
    CHECK_RET(ts.Listen());
    TcpSvr new_ts;
        struct sockaddr_in clientaddr;
        if(!ts.Accept(&new_ts, &clientaddr))
        {
            return 0;
        }
    while(1)
    {

        std::string buf;
        new_ts.Recv(&buf);
        printf("chrome said : %s\n", buf.c_str());

        //C
        //正文
       // std::string body = "<html><h1>hello linux68</h1></html>";
       // //响应首行， 响应头部
       // char buffer[10240] = {0};
       // snprintf(buffer, sizeof(buffer) - 1, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %lu\r\n\r\n", "text/html", body.size());
       // std::string header;
       // header.assign(buffer, strlen(buffer));
       // printf("header : %s\n", header.c_str());
       // new_ts.Send(header);
       // new_ts.Send(body);


        //C++
        //std::string body = "<html><h1>hello linux68</h1></html>";
        ////响应首行， 响应头部
        //std::stringstream ss;
        //ss << "HTTP/1.1 200 OK\r\n";
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: " << body.size() << "\r\n";
        //ss << "\r\n";
        //std::string header = ss.str();
        //new_ts.Send(header);
        //new_ts.Send(body);

        //std::string body = "<html><h1>hello linux68</h1></html>";
        ////响应首行， 响应头部
        //std::stringstream ss;
        //ss << "HTTP/1.1 302 OK\r\n";
        //ss << "Content-Type: text/html\r\n";
        //ss << "Content-Length: " << body.size() << "\r\n";
        //ss << "Location: https://www.baidu.com\r\n";
        //ss << "\r\n";
        //std::string header = ss.str();
        //new_ts.Send(header);
        //new_ts.Send(body);
#if 0
        std::string body = "<html><h1>hello linux68</h1></html>";
        //响应首行， 响应头部
        std::stringstream ss;
        ss << "HTTP/1.1 404 Page Not Found\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: " << body.size() << "\r\n";
        ss << "\r\n";
        std::string header = ss.str();
        new_ts.Send(header);
        new_ts.Send(body);
#endif

        std::string body = "<html><h1>hello linux68</h1></html>";
        //响应首行， 响应头部
        std::stringstream ss;
        ss << "HTTP/1.1 502 Bad Gateway\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: " << body.size() << "\r\n";
        ss << "\r\n";
        std::string header = ss.str();
        new_ts.Send(header);
        new_ts.Send(body);
    }
    new_ts.Close();
    ts.Close();
    return 0;
}
