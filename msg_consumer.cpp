/*
 * @Author: LeiJiulong
 * @Date: 2024-10-21 19:19:08
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-10-21 21:02:45
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
#include <signal.h>
#include <iostream>


int msgid;
int LOOP = 1;

static  void sig_handler(int signo)
{
    if(signo == 2)
    {
        LOOP = 0;
        msgctl(msgid, IPC_RMID,NULL);
    }
}

int main()
{
    signal(SIGINT, sig_handler);

    key_t key;
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
    int i = 0;
    while(LOOP)
    {
        msgrcv(msgid,&buf,sizeof(Data), MTYPE, 0);
        printf("gender: %c\tid_no: %d\tpname: %s \t%d\n", buf.mdata.gender, buf.mdata.id_no, buf.mdata.pname, i++);
        std::cout << buf.mdata.pname << std::endl; 
    }
    msgctl(msgid, IPC_RMID,NULL);
    // buf.mtype = MTYPE;
    // buf.mdata.gender = (rand() % 2 == 0 ? 'M' : 'F');
    // buf.mdata.id_no = rand() % 1000;
    // // strcpy(buf.mdata.pname,"LeiJiulong");
    // snprintf(buf.mdata.pname, 64, "NAME-%03d", rand() % 1000);
    // msgsnd(msgid, &buf, sizeof(struct msgbuf) - sizeof(long), 0);
    return 0;
}
