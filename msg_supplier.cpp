/*
 * @Author: LeiJiulong
 * @Date: 2024-10-21 19:14:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-21 21:04:57
 * @Description:
 */

#include "mymsg.h"
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
#include <string>
#include <time.h>

int main()
{

    key_t key;
    int msgid;
    int fd = open(MSG_PATH, O_CREAT | O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("file open");
        return -1;
    }
    key = ftok(MSG_PATH, 0);
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }

    msgid = msgget(key, 0644 | IPC_CREAT);
    if (msgid < 0)
    {
        perror("msgget");
        return -1;
    }
    printf("msgid = %d\n", msgid);
    struct my_msgbuf buf;
    buf.mtype = MTYPE;
    std::string name = "LeiJiulong";
    for (int i = 0; i < 1000; i++)
    {
        buf.mdata.gender = ((rand() % 2) == 0 ? 'M' : 'F');
        buf.mdata.id_no = rand() % 1000;
        memset(buf.mdata.pname, 0, sizeof(buf.mdata.pname));
        // strcpy(buf.mdata.pname,name.c_str());
        snprintf(buf.mdata.pname, sizeof(buf.mdata.pname), "Name-%03d", rand() % 1000);
        // printf("%s\n", buf.mdata.pname);
        msgsnd(msgid, &buf, sizeof(struct my_msgbuf) - sizeof(long), 0);
        printf("sizeof buf: %ld\n", sizeof(buf));
        sleep(1);
    }
    return 0;
}
