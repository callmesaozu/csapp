#include <stdlib.h>
#include <stdio.h>
/* clock example: frequency of primes */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

typedef int data_t;
typedef struct
{
	long int len;
	data_t *data;
} vec_rec, *vec_ptr;

//这个函数增加了许多边界检查
vec_ptr new_vec(long int len);
//如果index合理，那么将v中的第index个data_t储存到*dest中，并返回1，否则返回0
int get_vec_element(vec_ptr v, long int index, data_t *dest);
long int vec_length(vec_ptr v);
//如果是下面这种，combine1计算v中data_t元素的加法
#define IDENT 0
#define OP +
//如果是下面这种，combine1计算v中data_t元素的乘法
//#define IDENT 1;
//#define OP *

void combine1(vec_ptr v, data_t *dest);





int main()
{
	vec_ptr teVec;
	teVec = new_vec(1000000000L);
	data_t dest;
	combine1(teVec, &dest);
	printf("combine1 %d\n", (int)dest);
	
	clock_t t;
	t = clock();
	printf ("Calculating...\n");
	combine1(teVec, &dest);
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	t = clock();
	combine4(teVec, &dest);
	t = clock() - t;
	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	return 0;
}


vec_ptr new_vec(long int len)
{
	vec_ptr result = (vec_ptr)malloc(sizeof(vec_rec));
	if(!result)
	{
		return NULL;
	}
	result->len = len;
	if(len > 0)
	{
		data_t *data = (data_t *)calloc(len, sizeof(data_t));
		if(!data)
		{
			free((void *)result);
			return NULL;
		}
		result->data = data;
	}
	else
	{
		result->data = NULL;
	}
	return result;
}


int get_vec_element(vec_ptr v, long int index, data_t *dest)
{
	if(index < 0 || index >= v->len)
	{
		return 0;
	}
	*dest = v->data[index];
	return 1;
}

long int vec_length(vec_ptr v)
{
	return v->len;
}

void combine1(vec_ptr v, data_t *dest)
{
	long int i;
	
	*dest = IDENT;
	for(i = 0; i < vec_length(v); i++)
	{
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}
//combine2combine1作出的优化就是把计算长度移出了循环
//称为代码移动，相对于GCC的O1优化，确实能够提升效率
//程序员必须经常帮助编译器显式地完成代码移动
void combine2(vec_ptr v, data_t *dest)
{
	long int i;
	
	*dest = IDENT;
	long int length = vec_length(v);
	for(i = 0; i < length; i++)
	{
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}
data_t *get_vec_start(vec_ptr v)
{
	return v->data;
}
//和combine2相比，combine3直接访问数组元素，减少了程序调用
//但并没有显著提升效率，而是只提升了一点
//这种优化称之为减少过程调用
//直接访问数组还破坏了程序的模块性
//效率和模块性经常会有冲突
void combine3(vec_ptr v, data_t *dest)
{
	long int i;
	long int length = vec_length(v);
	data_t *data = get_vec_start(v);
	
	*dest = IDENT;
	for(i = 0; i < length; i++)
	{
		*dest = *dest OP data[i];
	}
}


//combine3的for循环中，每次都是先取主存中的数据，再计算，计算的结果在放到主存中
//这样非常浪费时间
//可以增加临时变量，计算结果储存在临时变量中，计算结束后再放到主存中
//注意临时变量是放在寄存器中的
//这种优化消除了不必要的存储器引用
//可以显著提升效率，和我以前认为的不同
//以前我认为临时变量的空间分配需要占用大量时间
//所以确实是能不用指针的时候就不用指针
void combine4(vec_ptr v, data_t *dest)
{
	long int i;
	long int length = vec_length(v);
	data_t *data = get_vec_start(v);
	data_t acc = IDENT;
	
	for(i = 0; i < length; i++)
	{
		acc = acc OP data[i];
	}
	*dest = acc;
}

size_t strlen2( const char *s);
//lower1的时间复杂度是n^2级的
void lower1(char *s)
{
	int i;
	for(i = 0; i < strlen2(s); i++)
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
			s[i] -= ('A' - 'a');
	}
}
//lower2的时间复杂度是n
void lower2(char *s)
{
	int i;
	int len = strlen2(s);
	for(i = 0; i < len; i++)
	{
		if(s[i] >= 'A' && s[i] <= 'Z')
			s[i] -= ('A' - 'a');
	}
}
//书中的错误，size_t应是unsigned,strlen函数的简化版	
size_t strlen2( const char *s)
{
	int length = 0;
	while(*s != '\0')
	{
		s++;
		length++;
	}
	return length;
}
