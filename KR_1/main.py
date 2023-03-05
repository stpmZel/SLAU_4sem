import matplotlib.pyplot as plt
import numpy as np

f1 = np.array([float(item) for item in (open("f1.txt", "r+"))][:20])
f2 = np.array([float(item) for item in (open("f2.txt", "r+"))])
f3 = np.array([float(item) for item in (open("f3.txt", "r+"))])
n1 = np.array([float(item) for item in (open("n1.txt", "r+"))][:20])
n2 = np.array([float(item) for item in (open("n2.txt", "r+"))])
n3 = np.array([float(item) for item in (open("n3.txt", "r+"))])



fig, ax = plt.subplots(figsize=(8, 5), dpi=150)

fig.suptitle("log(t) от n",
             fontsize='xx-large')

plt.grid(True)

plt.xticks(np.arange(-1, 100, 5))


ax.plot(n1, np.log(f1), label='FIP')
ax.plot(n2, np.log(f2), label='Gaus-Zeidel')
ax.plot(n3, np.log(f3), label='Jacobi')
ax.legend(loc='best', fontsize=12)
plt.xlabel('n', fontsize=14)
plt.savefig("plot.png")
plt.show()
