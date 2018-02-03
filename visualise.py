import numpy as np
from matplotlib import pyplot as plt



m = np.loadtxt("coords1.txt",skiprows=1)
edges = np.loadtxt("ans1.txt",dtype=np.int)

x,y = m.T
plt.scatter(x,y)


plt.plot(x[edges.T], y[edges.T], 'r-')


plt.show()
