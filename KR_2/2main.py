import matplotlib.pyplot as plt
import numpy as np
import matplotlib.ticker as ticker

x1 = np.array([])
y1 = np.array([])
with open('x_y1.txt') as f1:
    for line in f1:
        a, b = line.split()
        x1 = np.append(x1, float(a))
        y1 = np.append(y1, float(b))

x2 = np.array([])
y2 = np.array([])
with open('x_y2.txt') as f1:
    for line in f1:
        a, b = line.split()
        x2 = np.append(x2, float(a))
        y2 = np.append(y2, float(b))

x3 = np.array([])
y3 = np.array([])
with open('x_y3.txt') as f1:
    for line in f1:
        a, b = line.split()
        x3 = np.append(x3, float(a))
        y3 = np.append(y3, float(b))


x4 = np.array([])
y4 = np.array([])
with open('x_y4.txt') as f1:
    for line in f1:
        a, b = line.split()
        x4 = np.append(x4, float(a))
        y4 = np.append(y4, float(b))


x5 = np.array([])
y5 = np.array([])
with open('x_y5.txt') as f1:
    for line in f1:
        a, b = line.split()
        x5 = np.append(x5, float(a))
        y5 = np.append(y5, float(b))


time = np.array([float(item) for item in (open("../KR_2/time.txt", "r+"))])
lam = np.array([float(item) for item in (open("../KR_2/lam.txt", "r+"))])



fig, ax = plt.subplots(figsize=(8, 5), dpi=150)

# fig.suptitle("log(t) от n",
#              fontsize='xx-large')

plt.grid(True)

plt.xticks(np.arange(-1, 3500, 5))
ax.xaxis.set_major_locator(ticker.MultipleLocator(5000))


ax.plot(x1, y1, linestyle="--",label='Градиентный спуск')
ax.plot(x2, y2, linestyle="--",label='Градиентный спуск с оптимальным tau')
ax.plot(x3, y3, linestyle="--",label='Наискорейший градиентный спуск')
ax.plot(x4, y4, linestyle="--",label='Градиентный спуск с ускорением чебышева')
ax.plot(x5, y5, linestyle="--",label='Сопряженные градиенты')

ax.scatter(x1, y1)
ax.scatter(x2, y2)
ax.scatter(x3, y3)
ax.scatter(x4, y4)
ax.scatter(x5, y5)


ax.legend(loc='best', fontsize=12)
plt.xlabel('x', fontsize=14)
plt.xlabel('y', fontsize=14)
plt.savefig("plot_3.png")
plt.show()
