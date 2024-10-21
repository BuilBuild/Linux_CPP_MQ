/*
 * @Author: LeiJiulong
 * @Date: 2024-10-21 19:15:23
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-21 19:26:09
 * @Description:
 */
#pragma once

#define MTYPE 1

#define MSG_PATH "./mason"

typedef struct data_s
{
    int id_no;
    char gender;
    char pname[64];
} Data;

struct my_msgbuf 
{
    long mtype;
    Data mdata;
};
