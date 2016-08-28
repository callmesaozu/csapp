/*✗ gcc -o echoservert_pre echoservert_pre.c echo_cnt.c sbuf.o ../csapp.c -lpthread -pthread*/
/*echoservert_pre.c: In function ‘main’:*/
/*echoservert_pre.c:25:5: warning: implicit declaration of function ‘sbuf_init’ [-Wimplicit-function-declaration]*/
/*     sbuf_init(&sbuf, SBUFSIZE);*/
/*     ^*/
/*echoservert_pre.c:35:9: warning: implicit declaration of function ‘sbuf_insert’ [-Wimplicit-function-declaration]*/
/*         sbuf_insert(&sbuf, connfd);*/
/*         ^*/
/*echoservert_pre.c: In function ‘thread’:*/
/*echoservert_pre.c:44:22: warning: implicit declaration of function ‘sbuf_remove’ [-Wimplicit-function-declaration]*/
/*         int connfd = sbuf_remove(&sbuf);*/
/*出现以上警告，原因是这几个函数在使用前没有声明，当时我用的include头文件语句是“#include "sbuf.h"”，*/
/*解决办法有两个，一是#include "./sbuf.h"， 二是在main函数之前把声明放上去*/



#include "../csapp.h"
#include "./sbuf.h"
#define NTHREADS 4  //最多连接4个客户端
#define SBUFSIZE 16

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;    //shared buffer of connected descripters

int main(int argc, char **argv)
{
    int i, listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    pthread_t tid;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);
    sbuf_init(&sbuf, SBUFSIZE);
    listenfd = Open_listenfd(port);

    for (i = 0; i < NTHREADS; i++)
        Pthread_create(&tid, NULL, thread, NULL);

    while (1)
    {
        //因为connfd不是共享变量，因此不需要锁
        connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
    }  
}

void *thread(void *vargp)
{
    Pthread_detach(pthread_self());
    while (1)
    {
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        Close(connfd);
    }
}
