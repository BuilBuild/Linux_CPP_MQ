/*
 * @Author: LeiJiulong
 * @Date: 2024-10-21 21:22:24
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-21 21:22:25
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
    MyMSG<Data, CONSUMER> consumer(path, 1);
    auto t = consumer.msgRcv();
    std::cout << t.age << "  " << t.name << std::endl;
}