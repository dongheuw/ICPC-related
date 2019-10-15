f = [[0 for j in range(52)] for i in range(52)]
for i in range(52):
	f[0][i] = 1
for i in range(1,52):
	for j in range(1,52):
		for k in range(1,i+1):
			f[i][j] += f[k-1][j-1] * f[i-k][j]
T = 0
while True:
	import sys
	(n,k) = map(int,sys.stdin.readline().split())
	if n == 0 and k == 0: 
		break
	T += 1
	if T > 1:
		print
	print ("%s %d: %d" % ('Case',T,f[n][k]-f[n][k-1]))
