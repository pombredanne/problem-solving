A,B,X = map(int, input().split())
ans = a = b = 0

if  X % 500 != 0:  X += 500 - X%500
if  A < B: 
    a = X//1000 + (1 if (X%1000>0) else 0)
elif A > 2*B:
    b = X//500
else:
    a = X//1000; X %= 1000
    b = X//500

print(A*a + B*b)
