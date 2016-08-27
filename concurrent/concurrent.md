# 并发编程

- 访问慢速IO设备
- 与人交互
- 通过推迟工作以降低延迟
- 服务多个网络客户端
- 在多核计算机上进行并行计算

并发程序， 应用级并发的应用程序
- 进程
    - 进程间通信，IPC
- IO多路复用
    - 应用程序在一个进程的上下文中显示地调度它们自己的逻辑流
- 线程
    - 运行在一个单一进程上下文中的逻辑流，由内核调度

## 基于进程的并发编程

- `fork`、`execve`、`waitpid`

1. 服务器正在监听一个监听描述符上的连接请求(比如描述符3)
2. 服务器接受了客户端1的连接请求，并返回一个已连接描述符（描述符4）
3. 服务器派生一个子进程，该子进程获得服务器描述符表的完整拷贝
4. 子进程关闭它的拷贝的监听描述符3，父进程关闭它的已连接描述符4（这一点至关重要）
5. 如果有客户端2请求连接，同上

### 基于进程的并发服务器

- 参考`echoserverp`
- `SIGCHLD`处理程序，回收所有僵死进程的资源(web服务器会运行很长时间)
    - `SIGCHLD`是阻塞的，而UNIX信号不排队，因此处理程序必须准备好回收多个僵尸子进程资源
- 父子进程必须关闭它们各自的 `connfd`拷贝，避免存储器泄露
- 因为套接字的文件表项中的引用计数，直到父子进程的`connfd`都关闭了，到客户端的连接才会终止


------
`echoserverp`：
```C
#include "../csapp.h"
void echo(int connfd);

void sigchld_handler(int sig)
{
    while (waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}

int main(int argc, char **argv)
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(port);
    while (1)
    {
        connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
        if (Fork() == 0)
        {
            Close(listenfd);
            echo(connfd);
            Close(connfd);
            exit(0);
        }
        Close(connfd);
    }  
}
```

### 关于进程的优劣

- 优点：独立的地址空间，虚拟存储器的分配由操作系统负责，不需要应用程序处理
- 缺点：独立的地址空间使得进程共享状态信息变得困难
    - 必须使用显示的IPC机制
    - 由于进程控制和IPC开销很高，基于进程的设计往往比较慢

- IPC机制
    - `waitpid`和UNIX信号是基本的，允许进程发送小消息到同一主机上的其他进程
    - 套接字接口， 不同主机上的进程间交换任意的字节流
    - UNIX IPC：所有允许进程和同一台主机上与其他进程进行通信的技术
        - 管道
        - 先进先出
        - 系统V共享存储器
        - 系统V信号量（semaphore）
        > 参考W.R.Stevens. UNIX Network Programming: Interprocessn Communications, Second Edition.

## 基于I/O多路复用的并发编程

- `select`函数，要求内核挂起进程，只有在一个或多个IO事件发生后，才将控制返回给应用程序

```C
#include <sys/select.h>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, struct timeval *timeout);
            //返回已准备好的描述符的非零的个数，若出错则返回-1
/*csapp中使用了简化的select函数:*/
int select(int n, fd_set *fset, NULL,NULL, NULL);
			//n是描述符集合的最大基数

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
            //处理描述符集合的宏
```

`select`函数处理类型为`fd_set`的集合，也叫描述符集合，描述符集合为n位的位向量：$ b_{n-1},\cdots , b_{1},b_{0} $

只允许对描述符集合做三件事：
- 分配它们
- 将此种类型的变量复制给另一个变量
- 用`FD_CLR`、`FD_ISSET`、`FD_SET`、`FD_ZERO`宏指令修改它们
- `select`函数会修改`fset`指向的`fd_set`，指向读集合中一个称为**准备好集合的子集**,返回**准备好集合的子集**的基数，因此在调用`select`时都更新读集合

```C
#include "../csapp.h"
void echo(int connfd);
void command(void);

int main(int argc, char **argv)
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);

    FD_ZERO(&read_set);                 //清空read set
    FD_SET(STDIN_FILENO, &read_set);    //add stdin to read set
    FD_SET(listenfd, &read_set);        //add listenfd to read set

    while (1)
    {
        ready_set = read_set;
        Select(listenfd + 1, &ready_set, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &ready_set))
            command();
        if (FD_ISSET(listenfd, &ready_set))
        {
            connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
            echo(connfd);
            Close(connfd);
        }
    }
}


void echo(int connfd)
{
	size_t n;
	char buf[MAXLINE];
	rio_t rio;
	
	Rio_readinitb(&rio, connfd);
	while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
	{
		printf("server received %d bytes\n", (int)n);
		Rio_writen(connfd, buf, n);
	}
}

void command(void)
{
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
        exit(0);
    printf("%s", buf);
}

/* 输出 */
✗ ./select 8000
sdad
sdad
server received 6 bytes	//在客户端保持连接时在服务器端输入asdsadsd不会立即输出，而是要等到客户端连接结束，粒度不够细
asdsadsd
asdsadsd
```

### 基于IO多路复用的并发事件驱动服务器

- 优势
	- 比基于进程的设计给了程序员更多的对于程序行为的控制
		- 如编写一个事件驱动的并发服务器，为某些客户端提供所需的服务
	- 运行在单一进程上下文中
    	- 每个逻辑流都能访问该进程的全部地址空间，使得流之间共享数据变得容易
		- 可以利用熟悉的调试工具，如GDB，调试并发服务器
		- 不需要上下文切换，因此更高效
- 缺点
	- 编码复杂，随着粒度减小，复杂性还会上升
	- 不能充分利用多核处理器

```C
#include "../csapp.h"

typedef struct 
{
    int maxfd;          //largest description in read_set;
    fd_set read_set;    //set of all active descriptions;
    fd_set ready_set;   //subset of descriptions ready for reading;
    int nready;         //number of ready descriptions from select;
    int maxi;           //highwater index into client away;
    int clientfd[FD_SETSIZE];   //set of active descriptions;
    rio_t clientrio[FD_SETSIZE];    //set of active read buffers;
} Pool;

void init_pool(int listenfd, Pool *p);
void add_client(int connfd, Pool *p);
void check_client(Pool *p);

int byte_cnt = 0;   //counts total bytes recieved by server

int main(int argc, char **argv)
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    static Pool pool;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    init_pool(listenfd, &pool);

    while (1)
    {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        if (FD_ISSET(listenfd, &pool.ready_set))
        {
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        check_client(&pool);
    }

}

void init_pool(int listenfd, Pool *p)
{
    int i;
    p->maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
    {
            p->clientfd[i] = -1;
    }

    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, Pool *p)
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++)
    {
        if (p->clientfd[i] < 0)
        {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            FD_SET(connfd, &p->read_set);

            if (connfd > p->maxfd)
                p->maxfd = connfd;
            if (i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    if (i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void check_client(Pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi)&&(p->nready > 0); i++)
    {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
        {
            p->nready--;
            if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
            {
                byte_cnt += n;
                printf("Server recieved %d (%d total) bytes on fd %d\n", 
                        n, byte_cnt, connfd);
                Rio_writen(connfd, buf, n);
            }
            else
            {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}
```

## 基于线程的并发编程

- 线程
    - 是运行在进程上下文中的逻辑流
    - 由内核自动调度
    - 有自己的线程上下文(thread context)
    	- 唯一的整数线程ID，thread id TID
    	- 栈
    	- 栈指针
    	- 程序计数器
    	- 通用目的寄存器
    	- 条件码
    - 所有运行在一个进程里的线程共享该进程的整个虚拟地址空间
    	- 代码
    	- 数据
    	- 堆
    	- 共享库
    	- 打开的文件

### 线程执行模型

- 线程的上下文比进程小的多，切换快得多
- 一个和进程相关的线程组成一个对等线程池
	- 主线程和其他线程的区别仅仅在于它总是进程中第一个运行的线程
	- 一个线程可以杀死它的任何对等线程，或者等待它的任何对等线程终止
	- 每个对等线程都能读写相同的共享数据

### posix线程

- C程序中处理线程的一个标准接口

```C
#include "../csapp.h"
void *thread(void *vargp);

int main()
{
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL);
    Pthread_join(tid, NULL);
    exit(0);
}

void *thread(void *vargp)
{
    printf("Hello, world!\n");
    return NULL;
}
```

- 创建线程

```C
#include <pthread.h>

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                  void *(*start_routine) (void *), void *arg);
                  //若成功则返回0，若出错则非零
                  //在新线程的上下文中运行start_routine（线程例程，即函数）
                  //arg，输入变量
                  //attr参数修改新线程的默认属性


pthread_t pthread_self(void);
				//返回调用者的线程ID
/* Compile and link with -pthread. */
```

- 终止线程
	- 当顶层的线程例程返回时，线程会隐式地终止
	- 调用`pthread_exit`函数，线程会显式地终止
		- 如果主线程调用`pthread_exit`，它会等待所有其他对等线程终止，然后终止主线程和整个进程，返回值为`thread_return`
	- 某个对等线程调用`exit`函数，终止进程以及所有与该进程相关的线程
	- 另一个对等线程通过以当前线程ID作为参数，调用`pthread_cancle`，终止当前线程

```C
#include <pthread.h>
void pthread_exit(void *retval);
	//成功则返回0，出错则非零
int pthread_exit(pthread_t tid);
	//成功则返回0，出错则非零

Compile and link with -pthread.
```



