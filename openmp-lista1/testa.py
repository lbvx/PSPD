with open('out.txt', 'r') as f:
    a1 = set(int(l) for l in f)

with open('out_omp.txt', 'r') as f:
    a2 = list(int(l) for l in f)

for i in range(300000):
    if a2.count(i) == 1:
        a2.remove(i)

print(a2)
