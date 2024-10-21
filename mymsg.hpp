/*
 * @Author: LeiJiulong
 * @Date: 2024-10-21 19:27:24
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-21 21:08:15
 * @Description:
 */
#pragma once

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>

/**
 * @Author: LeiJiulong
 * @description: 用于区分消息操作对象类型
 * @return {*}
 */
enum USER_TYPE
{
    CONSUMER,
    SUPPLIER
};

template <typename T, USER_TYPE TP>
class MyMSG
{
public:
    typedef struct
    {
        long mtype;
        T mdata;
    } my_msgbuf;

private:
    std::string file_path;
    long MSG_LEVEL;
    int msgid;
    key_t key;
    my_msgbuf msg_template;

public:
    MyMSG(std::string &paths, long MSG_LEVEL) : file_path(paths), MSG_LEVEL(MSG_LEVEL)
    {
        int fd = open(file_path.c_str(), O_CREAT | O_RDONLY, 0644);
        if (fd < 0)
        {
            perror("file open");
            exit(EXIT_FAILURE);
        }
        close(fd);
        key = ftok(file_path.c_str(), 0);
        msgid = msgget(key, 0644 | IPC_CREAT);
        if (msgid < 0)
        {
            perror("msgget");
            exit(EXIT_FAILURE);
        }
        msg_template.mtype = MSG_LEVEL;
    }
    ~MyMSG() {}
    void msgSend(T &t);
    T msgRcv();
    void msgDt();
};

/**
 * @Author: LeiJiulong
 * @description: SUPPLIER 发送消息
 * @return {*}
 */
template <typename T, USER_TYPE TP>
void MyMSG<T, TP>::msgSend(T &t)
{
    if (TP == CONSUMER)
    {
        printf("U are CONSUMER can't to send msg!");
        return;
    }
    // msg_template.mdata = t;
    my_msgbuf my_buf;
    my_buf.mtype = MSG_LEVEL;
    memcpy(&(my_buf.mdata), &t, sizeof(t));
    // std::cout << "size my_buf:  " << sizeof(my_buf) << std::endl;
    // std::cout << "size t input:  " << sizeof(t) << std::endl;
    // std::cout << "size long:  " << sizeof(long) << std::endl;
    // std::cout << "size mdata:  "  << sizeof(my_buf.mdata) << std::endl;
    int flag = msgsnd(msgid, &my_buf, sizeof(t), 0);
    if (flag < 0)
    {
        perror("msg send");
    }
}

/**
 * @Author: LeiJiulong
 * @description: CONSUMER 接收消息
 * @return {*}
 */
template <typename T, USER_TYPE TP>
T MyMSG<T, TP>::msgRcv()
{
    T t{};
    if (TP == SUPPLIER)
    {
        printf("U are SUPPLIER can't to recv msg!");
        return t;
    }

    // std::cout << "msgrcv size: " <<  sizeof(t) << std::endl;
    int flag = msgrcv(msgid, &t, sizeof(t), MSG_LEVEL, 0);
    // std::cout << "flag:  " << flag << std::endl;

    return t;
}

template <typename T, USER_TYPE TP>
void MyMSG<T, TP>::msgDt()
{
}
