def hanoi(n, src, dst, tmp):
	if n <= 0:
		pass
	else:
		for h in hanoi(n-1, src, tmp, dst):
			yield h
		yield (src, dst)
		for h in hanoi(n-1, tmp, dst, src):
			yield h

def hanoi2(n, src, dst, tmp):
	if n <= 0:
		return
	hanoi2(n-1, src, tmp, dst)
	print (src, dst)
	hanoi2(n-1, tmp, dst, src)

if __name__ == '__main__':
	print [h for h in hanoi(3, 1, 3, 2)]
	hanoi2(3, 1, 3, 2)