values = {'0': 1, '6': 1, '8': 2, '9': 1}
N = input()
for i in range(int(N)):
    line = input()
    print(sum(map(lambda x: values.get(x, 0), line)))
