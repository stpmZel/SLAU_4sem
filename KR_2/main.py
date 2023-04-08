import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

f1 = np.array([float(item) for item in (open("../KR_2/1.txt", "r+"))])
f2 = np.array([float(item) for item in (open("../KR_2/2.txt", "r+"))])
f3 = np.array([float(item) for item in (open("../KR_2/3.txt", "r+"))])
f4 = np.array([float(item) for item in (open("../KR_2/4.txt", "r+"))])
n1 = np.array([float(item) for item in (open("../KR_2/n1.txt", "r+"))])
n2 = np.array([float(item) for item in (open("../KR_2/n2.txt", "r+"))])
n3 = np.array([float(item) for item in (open("../KR_2/n3.txt", "r+"))])
n4 = np.array([float(item) for item in (open("../KR_2/n4.txt", "r+"))])

time = np.array([float(item) for item in (open("../KR_2/time.txt", "r+"))])
lam = np.array([float(item) for item in (open("../KR_2/lam.txt", "r+"))])



fig, ax = plt.subplots(figsize=(8, 5), dpi=150)

# fig.suptitle("log(t) от n",
#              fontsize='xx-large')

plt.grid(True)

plt.xticks(np.arange(-1, 3500, 5))
ax.xaxis.set_major_locator(ticker.MultipleLocator(5000))


# ax.plot(n1, np.log(f1), label='Градиентный спуск с tau = 1 / λmax;')
# ax.plot(n2, np.log(f2), label='Градиентный спуск с оптимальным параметром;')
# ax.plot(n3, np.log(f3), label='Градиентный спуск с ускорением Чебышева')
# ax.plot(n4, np.log(f4), label='Симметризованны1 метод (SSOR)')

ax.plot(lam, time, label='время от delta_lam')


ax.legend(loc='best', fontsize=12)
plt.xlabel('dela_lam', fontsize=14)
plt.savefig("plot2.png")
plt.show()
