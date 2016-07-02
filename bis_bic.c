//2.13
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int bool_or(int x, int y)
{
	return x|y;
}

int bool_xor(int x, int y)
{
	return x^y;
}
//在m为1的每个位置上，将z对应的位置1
int bis(int x, int m)
{
	return bool_or(x, m);
}
//在m为1的每个位置上，将z对应的位置0
int bic(int x, int m)
{
	return bool_xor(x, m);
}

bool isEqual(int x, int y)
{
	return !(x^y);
}

typedef unsigned char *byte_pointer;

void show_byte(byte_pointer start, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%.2x", start[i]);
	}
	printf("\n");
}

void show_int(int x)
{
	show_byte((byte_pointer) &x, sizeof(int));
}

void show_float(float x)
{
	show_byte((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x)
{
	show_byte((byte_pointer) &x, sizeof(void *));
}

float sum_elements(float a[], unsigned length)
{
	int i;
	float result = 0;
	
	for (i = 0; i <= length -1; i++)
	{
		result += a[i];
	}
	return result;
}

int strlonger( char *s, char *t)
{
	//return strlen(s) - strlen(t) > 0;
	return (int)strlen(s) - (int)strlen(t) > 0;
}

bool tadd_ok(int x, int y)
{
	if(((x>0)&&(y>0)&&(x+y<0))||((x<0)&&(y<0)&&(x+y>=0)))
	{
		return true;	//不会产生溢出
	}
	else
	{
		return false;
	}
}

bool tsub_ok(int x, int y)	//判断x-y是否能够相减
{
	int t = sizeof(int);
	int m = 1 << t * 8 - 1;
	return (y != m) && (tadd_ok(x, -y));
}

typedef struct 
{
	char *a;
	short b;
	char c;
	char d;
	double e;
	long long f;
	float g;
	void *h;
} U3;

typedef struct 
{
	double a;
	long long b;
	float c;
	char *d;
	void *e;
	short f;
	char g;
	char h;
} U4;

int func(int x, int *y)
{
	printf("x = %d, *y = %d\n", x, *y);
	return 0;
}

int main()
{
/*	int x = 0x81462146;*/
/*	int y = 0x46214621;*/
/*	printf("x = 0x%x = %d\n", x, x);*/
/*	printf("y = 0x%x = %d\n", y, y);*/
/*	printf("bic(x, y) = 0x%x\n", bic(x, y));*/
/*	printf("bis(x, y) = 0x%x\n", bis(x, y));*/
/*	printf("x == y? %s\n", isEqual(x, y)?"true":"false");*/
/*	int k = 32;*/
/*	int m = x << k;*/
/*	int n = x >> k;*/
/*	printf("x << %d = 0x%x = %d\n", k, m, m);*/
/*	printf("x >> %d = 0x%x = %d\n", k, n, n);*/
/*	printf("1<<2+3<<4 = %d\n", 1<<2+3<<4);*/
/*	printf("sizeof(char) = %d\n", (int)sizeof(char));*/
/*	printf("sizeof(int) = %d\n", (int)sizeof(int));*/
/*	printf("sizeof(unsigned short) = %d\n", (int)sizeof(unsigned short));*/
/*	printf("sizeof(long) = %d\n", (int)sizeof(long));*/
/*	printf("sizeof(long long) = %d\n", (int)sizeof(long long));*/
/*	char a = 0xFF;*/
/*	printf("a = 0x%x = %d\n", a, a);*/

/*	short x = 12345;*/
/*	short mx = -x;*/
/*	printf("x = 0x%x = %d\n", x, x);*/
/*	printf("mx = 0x%x = %d\n", mx, mx);*/
/*	show_byte((byte_pointer) &x, sizeof(short));*/
/*	show_byte((byte_pointer) &mx, sizeof(short));*/

/*	short int v = -12345;*/
/*	unsigned short uv = (unsigned short) v;*/
/*	printf("v = %d, uv = %u\n", v, uv);*/
/*	printf("sizeof unsigned = %d\n", (int)sizeof(unsigned));*/
/*	unsigned u = 4294967295u;	//Umax_32*/
/*	int tu = (int) u;*/
/*	printf("u = 0x%x = %u\n", u, u);*/
/*	printf("tu = 0x%x = %d\n", tu, tu);*/
/*	printf("-2147483647 = 0x%x\n", -2147483647);*/
/*	printf("-2147483647-1 = %x\n", -2147483647-1);*/
/*	printf("(int)2147483648u = ox%x\n", 2147483648u);*/
/*	if((-2147483647-1u) < -2147483647)*/
/*	{*/
/*		printf("true\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("false\n");*/
/*	}*/
	

/*	short sx = -12345; 			//-12345*/
/*	unsigned short usx = sx; 	//53191*/
/*	int x = sx;					//-12345*/
/*	unsigned ux = usx;			//53191*/
/*	printf("sx = %d:\t", sx);*/
/*	show_byte((byte_pointer) &sx, sizeof(short));*/
/*	printf("usx = %u:\t", usx);*/
/*	show_byte((byte_pointer) &usx, sizeof(unsigned short));*/
/*	printf("x = %u:\t", x);*/
/*	show_byte((byte_pointer) &x, sizeof(int));*/
/*	printf("ux = %u:\t", ux);*/
/*	show_byte((byte_pointer) &ux, sizeof(unsigned));*/

/*	short sx = -12345; 			//-12345*/
/*	unsigned uy = sx;			//mystery!*/
/*	printf("uy = %u:\t", uy);*/
/*	show_byte((byte_pointer) &uy, sizeof(unsigned));*/

/*	int x = -53191;*/
/*	short sx = (short)x;*/
/*	int y = sx;*/
/*	printf("x = 0x%x:\t = %d:\t", x, x);*/
/*	show_byte((byte_pointer) &x, sizeof(int));*/
/*	printf("sx = 0x%x:\t = %d:\t", sx, sx);*/
/*	show_byte((byte_pointer) &sx, sizeof(short));*/
/*	printf("0-1u = 0x%x:\t = %u\n", 0-1u, 0-1u);*/
/*	float a[0];*/
/*	sum_elements(a, 0);*/
	
/*	char s1[] = "ab";*/
/*	char s2[] = "abc";*/
/*	if( strlonger(s1, s2))*/
/*	{*/
/*		printf("true\n");*/
/*	}*/
/*	else*/
/*	{*/
/*		printf("false\n");*/
/*	}*/
/*	short a = 0x1005;*/
/*	short b = 0x8010;*/
/*	short c = a - b;*/
/*	printf("a = 0x%x = %d\n", a, a);*/
/*	printf("b = 0x%x = %d\n", b, b);*/
/*	show_byte((byte_pointer) &c, sizeof(short));*/
/*	printf("a - b = 0x%x = %d\n", c, c);*/
/*	printf("sizeof int: %d\n", (int)sizeof(int));*/
/*	int y = 0x80000000;*/
/*	printf("y = 0x%x = %d\n", y, y);*/
/*	printf("-y = 0x%x = %d\n", -y, -y);*/
/*	printf("y+y = 0x%x = %d\n", y+y, y+y);*/
/*	int x = 1 << 4 * 8 - 1;*/
/*	int z = ~x;*/
/*	printf("x = 0x%x = %d\n", x, x);*/
/*	printf("~x = 0x%x = %d\n", z, z);*/

/*	float x = 1.0;*/
/*	show_float(x);	//大端顺序是3f800000;*/
/*	float y = 3510593.0;*/
/*	show_float(y);	//大端顺序是4a564504;*/

/*	printf("(int)+1e10 = %d\n", (int)+1e10);	//我的是2147483647*/

/*	printf("size of char * = %d\n", (int)sizeof(char*));*/
/*	printf("size of char   = %d\n", (int)sizeof(char));*/
	
	short *p;
	short d = 3;
	p = &d;
	printf("p = %u\n", (int *)p);
	printf("(int *)p + 7 = %u\n", (int *)p + 7);
	printf("(int *)(p + 7) = %u\n", (int *)(p + 7));
	printf("sizeof p = %d\n", (int)sizeof(p));
	
	int (*fp)(int , int *);
	fp = func;
	int y = 1;
	int result = fp(3, &y);

	return 0;
}


