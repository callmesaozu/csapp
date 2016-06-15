//csapp 3.12
void store_prod(num_t *dest, unsigned x, num_t y)
{
	*dest = x * y;
}

dest at %ebp + 8, x at %ebp + 12, y at %ebp + 16

movl 	12(%ebp), %eax
movl 	20(%ebp), %eax
imull 	%eax, %ecx
mull	16(%ebp)
leal 	(%ecx, %edx), %edx
movl	8(%ebp), %ecx
movl 	%eax, (%ecx)
movl 	%edx, 4(%ecx)


//csapp 3.22, 得到x中1数量的奇偶性, 若奇数则返回1
//x at %ebp + 8
	movl 	8(%ebp), %edx
	movl 	$0, %eax
	testl	%edx, %edx	//x|x
	je	.L7				//x == x
.L10:
	xorl	%edx, %eax
	shrl	%edx		//逻辑右移1位
	jne		.L10
.L7:
	andl	$1, %eax

//3.22的C程序
int func_a(unsigned x)
{
	int val = 0;
	while(x != 0)
	{
		val ^= x;
		x >>= 1;
	}
	return val & 1;
}


//3.26 除法
int arith(int x)
{
	return x / 4;
}
//等价的汇编代码
//register: x in %edx
leal	3(%edx), %eax
testl	%edx, %edx
cmovns	%edx, %eax
sarl	$2,	%eax



//switch, 跳转表，值得仔细阅读
int switch_eg(int x, int n)
{
	int result = x;
	switch (n)
	{
		case 100:
			result *= 13;
			break;
		
		case 102:
			result += 10;
			/*fall through*/
		
		case 103:
			result += 11;
			break;

		case 104:
		case 106:
			result * result;

		default:
			result = 0;
	}
	
	return result;
}
//等效的函数，只能用gcc编译，因为&&运算符可能是gcc特有的
int switch_eg_impl(int x, int n)
{
	static void *jt[7] = 
		{
			&&loc_A, &&loc_def, &&loc_B,
			&&loc_C, &&loc_D, &&loc_def,
			&&loc_D
		};//&&创建一个指向代码位置的指针
	
	unsigned index = n - 100;
	int result;
	
	if(index > 6)
		goto loc_def;
		
	//multiWay branch
	goto *jt[index];
	
	loc_def:	//default case
		result = 0;
		goto done;
		
	loc_C:		//103
		result = x;
		goto rest;
		
	loc_A:		//100
		result = x * 13;
		goto done;
		
	loc_B:		//102
		result = x + 10;
		//fall through
		
	rest:
		result += 11;
		goto done;
		
	loc_D:		//104, 106
		result = x * x;
		
	done:
		return result;
}
