/*
 * @Author: LeiJiulong
 * @Date: 2024-10-21 19:53:45
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-21 19:57:53
 * @Description:
 */
#include "mymsg.hpp"

typedef struct my_data
{
    char name[64];
    int age;
} Data;

int main()
{
    std::string path = "./test";
    MyMSG<Data, SUPPLIER> supplier(path, 1);
    Data dt {"LeiJiulong", 18};
    supplier.msgSend(dt);

}