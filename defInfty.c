//定义双精度正无穷，负无穷， 0
# define POS_INFINITY 2e308
# define NEG_INFINITY -2e308
# define NEG_ZERO -0.0

/*官方答案为：*/
/*# define POS_INFINITY 1e400*/
/*# define NEG_INFINITY (-POS_INFINITY)*/
/*# define NEG_ZERO (-1.0/POS_INFINITY)*/

#include <stdio.h>

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

int main()
{
	double x, y, z;
	x = (double)POS_INFINITY;
	y = (double)NEG_INFINITY;
	z = (double)NEG_ZERO;
	printf("POS_INFINITY = ");
	show_byte((byte_pointer) &x, sizeof(double));
	printf("NEG_INFINITY = ");
	show_byte((byte_pointer) &y, sizeof(double));
	printf("NEG_ZERO = ");
	show_byte((byte_pointer) &z, sizeof(double));
	return 0;
}
