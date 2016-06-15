def stepNum(n):
	"""获得n的阶乘
	"""
	stepNum = 1
	for i in range(1, n + 1):
		stepNum = stepNum * i
	return stepNum


