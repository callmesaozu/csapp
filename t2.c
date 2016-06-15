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
