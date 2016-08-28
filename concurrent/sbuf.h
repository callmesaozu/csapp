typedef struct {
    int *buf;       //buffer array;
    int n;          //max buf number of slots;
    int front;      //buf[(front + 1) %n] is first item;
    int rear;       //buf[rear %n] is last item;
    sem_t mutex;    //
    sem_t slots;    //空槽位数量
    sem_t items;    //可用项目的数量
} sbuf_t;

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);