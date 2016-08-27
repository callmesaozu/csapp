#include "../csapp.h"

#define WSIZE	4	//字大小
#define DSIZE	8	//双字大小
#define CHUNKSIZE	(1<<12)	//块大小,4kb

#define MAX(x, y)	((x) > (y)? (x): (y))

#define PACK(size, alloc)	((size) | (alloc))	//打包块头部

#define GET(p)	(*(unsigned int *)(p))	//读取p中存放的字
#define PUT(p, val)	(*(unsigned int *)(p) = (val))	//将val赋值给*p

#define GET_SIZE(p)	(GET(p) & ~0x7)	//从块头部获取块大小, 这个块大小是整个块的大小
#define GET_ALLOC(p)	(GET(p) & 0x1)	//是否分配

#define HDRP(bp)	((char *)(bp) - WSIZE)	//返回指向块头部的指针, bp其实指向有效元素
#define FTRP(bp)	((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)	//返回指向块脚部的指针

#define NEXT_BLKP(bp)	((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))	//返回指向后面块的快指针,很巧
#define PREV_BLKP(bp)	((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))	//返回指向前面块的快指针

static char *heap_listp;	//指向序言块中部的指针
static void *extend_heap(size_t words);	//扩展堆
void mm_free(void *bp);	//释放块
static void *coalesce(void *bp);	//合并空闲块
void *mm_malloc(size_t size);	//分配块
void place(void *bp, size_t asize);	//将sz大小的块分配给bp
static void *find_fit(size_t asize);	//找到能够放下asize大小的块


int mm_init(void)
{
	if ((heap_listp =mem_sbrk(4*WSIZE)) == (void *)-1)	//序言块8字节， 起始位置4字节， 结尾块4字节
		return -1;
		
	PUT(heap_listp, 0);								//起始位置
	PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));	//序言块头部
	PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));	//序言块尾部
	PUT(heap_listp + (3*WSIZE), PACK(0, 1));		//结尾块
	heap_listp += (2*WSIZE);
	
	if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
		return -1;
		
	return 0;
}

static void *extend_heap(size_t words)
{
	char *bp;
	size_t size;
	
	size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;	//如果不是8字节对齐，则再增加4字节
	if ((long)(bp = mem_sbrk(size)) == -1)	//如果不能扩展这么多字节,则返回空指针，否则bp为旧堆尾指针
		return NULL;
	
	PUT(HDRP(bp), PACK(size, 0)); //将新分配的空间设为未分配空间
	PUT(FTRP(bp), PACK(size, 0));	//新分配的空间块的块脚
	PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));	//重新设置结尾块
	
	return coalesce(bp);	//合并相邻的空闲块，返回指向合并后的块的块指针
}

void mm_free(void *bp)
{
	size_t size = GET_SIZE(HDRP(bp));
	
	PUT(HDRP(bp), PACK(size, 0));
	PUT(FTRP(bp), PACK(size, 0));	//将本块设置为空闲块
	coalesce(bp);	//合并空闲块
}

static void *coalesce(void *bp)
{
	size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));	//判断前一个块是否被分配
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));	//判断后一个块是否被分配
	size_t size = GET_SIZE(HDRP(bp));
	
	if (prev_alloc && next_alloc)	//如果前后块都已被分配，那么就不需要合并
	{
		return bp;
	}
	
	else if (prev_alloc && !next_alloc)	//如果前一个块被分配，后一个块空闲，那么合并后一个块
	{
		size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(bp), PACK(size, 0));
		//PUT(FTRP(bp), PACK(size, 0));	//这是书本上的代码，其实应该是将下一个空闲块的块脚设置为PACK(size, 0)
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));	//这行是我改的
	}
	
	else if (!prev_alloc && next_alloc)	//如果前一个块空闲，后一个块被分配， 那么合并前一个块
	{
		size += GET_SIZE(FTRP(PREV_BLKP(bp)));	//加上前一个块的大小；
		PUT(FTRP(bp), PACK(size, 0));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}
	
	else	//如果前后都空闲
	{
		size += GET_SIZE(FTRP(PREV_BLKP(bp))) +
			GET_SIZE(HDRP(NEXT_BLKP(bp)));
		PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
		bp = PREV_BLKP(bp);
	}
	
	return bp;
}

void *mm_malloc(size_t size)
{
	size_t asize;	//需要分配的块大小
	size_t extendsize;
	char *bp;
	
	if(size == 0)
		return NULL;
	
	if(size <= DSIZE)
	{
		asize = 2 * DSIZE;	//最小块就是16字节
	}
	else
	{
		asize = DSIZE * ((size + (DSIZE) + (DSIZE -1)) / DSIZE);//向上舍入
	}
	
	if ((bp = find_fit(asize)) != NULL)	//如果找合适的空闲块
	{
		place(bp, asize);
		return bp;
	}
	
	//否则就扩展
	extendsize = MAX(asize, CHUNKSIZE);
	if((bp = extend_heap(extendsize/WSIZE)) == NULL)	//如果扩展不了
		return NULL;
	place(bp, asize);
	return bp;
}

/*//这是我写的代码，没有考虑到剩余空间小于最小块的情况*/
/*void place(void *bp, size_t asize)*/
/*{*/
/*	size_t allSize = GET_SIZE(HDRP(bp));	//原始空闲块的大小*/
/*	PUT(HDRP(bp), PACK(asize, 1));*/
/*	PUT(FTRP(bp), PACK(asize, 1));	//分配块*/
/*	*/
/*	PUT(HDRP(NEXT_BLKP(bp)), PACK(allSize - asize, 0));*/
/*	PUT(FTRP(NEXT_BLKP(bp)), PACK(allSize - asize, 0));*/
/*}*/

void place(void *bp, size_t asize)
{
	size_t allSize = GET_SIZE(HDRP(bp));	//原始空闲块的大小
	
	if((allSize - asize) >= (2*DSIZE))
	{
		PUT(HDRP(bp), PACK(asize, 1));
		PUT(FTRP(bp), PACK(asize, 1));	//分配块
		
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK(allSize - asize, 0));
		PUT(FTRP(bp), PACK(allSize - asize, 0));
	}
	
	else
	{
		PUT(HDRP(bp), PACK(allSize, 1));
		PUT(FTRP(bp), PACK(allSize, 1));	//分配块
	}
}

static void *find_fit(size_t asize)	//这是首次适配方法
{
	void *bp;
	
	for(bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
	{
		if(!GET_ALLOC(bp) && (asize <= GET_SIZE(HDRP(bp))))
			return bp;
	}
	
	return NULL;
}
