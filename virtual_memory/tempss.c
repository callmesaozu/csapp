void bufoverflow()
{
	char buf[64];
	gets(buf);	//此处应该用fgets
	//char *fgets(char *s, int size, FILE *stream);
	return;
}

int *binheapDelete(int **binheap, int *size)
{
	int *packet = binheap[0];
	
	binheap[0] = binheap[*size - 1];
	*size--;	//应是(*size)--
	heapify(binheap, *size, 0);
	return(packet);
}

int *search(int *p, int val)
{
	while(*p && *p != val)
	{
		p += sizeof(int);	//事实上只要p++
	}
	return p;
}

int *stackref()
{
	int val;
	return &val;	//return时val已经被删除
}

int *heapref(int n, int m)
{
	int i;
	int *x, *y;
	
	x = (int *)Malloc(n *sizeof(int));
	
	/* ... */
	
	free(x);
	
	y = (int *)Malloc(m * sizeof(int));
	for(i = 0; i < m; i++)
		y[i] = x[i]++;	//此处x已被释放
	return y;
}

void leak(int n)
{
	int *x = (int *)Malloc(n * sizeof(int));
	
	return;
}
