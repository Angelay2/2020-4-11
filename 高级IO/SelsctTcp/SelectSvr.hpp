/*================================================================
*   
*   文件名称：SelectSvr.hpp
*   创 建 者：Angela
*   创建日期：2020年07月12日
*   描    述：
*
================================================================*/

#pragma once
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

class SelectSvr
{
    public:
        SelectSvr()
        {
            max_fd_ = -1;
            //清空事件集合
            FD_ZERO(&readfds_);
        }

        
        ~SelectSvr()
        {
        }

        //添加文件描述符到事件集合当中
        void AddFd(int fd)
        {
            //1.添加文件描述符到事件集合当中
            FD_SET(fd, &readfds_);
            //2.更新最大文件描述符的数值
            if(fd > max_fd_)
            {
                max_fd_ = fd;
            }
        }

        //移除文件描述符从事件集合当中
        void DeleteFd(int fd)
        {
            //1.移除
            FD_CLR(fd, &readfds_);
            //2.更新最大文件描述符数值
            for(int i = max_fd_; i >= 0; i--)
            {
                //1 2 3 4 5 6 7 8 9   max_fd_ : 9
                //9 8 7 6 5 4 3 2 1
                if(FD_ISSET(i, &readfds_) == 0)
                {
                    continue;
                }

                max_fd_ = i;
                break;
            }
        }

        //监控接口
        bool SelectWait()
        {

        }
    private:
        //由于select的第一个参数，需要在类的成员变量当中保存目前最大的文件描述符数值
        int max_fd_;
        fd_set readfds_;
};

