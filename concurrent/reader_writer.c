int readcnt;    //初始为0
sem_t mutex, w; //均初始为1

void reader(void)
{
    while (1)
    {
        P(&mutex);
        readcnt++;
        if (readcnt == 1)   //first in
            P(&w);
        V(&mutex);

        /* 读取过程 */

        P(&mutex);
        readcnt--;
        if (readcnt == 0)
            V(&w);
        V(&mutex);
    }
}

void writer(void)
{
    while (1)
    {
        P(&w);

        /* 写入过程 */

        V(&w);
    }
}