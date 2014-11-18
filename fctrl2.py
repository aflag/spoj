def fat(n):
    c = 1
    for i in xrange(2,n+1):
        c *= i
    return c

t = int(raw_input())
for i in xrange(t):
    n = int(raw_input())
    print fat(n)
