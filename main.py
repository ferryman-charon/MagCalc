import numpy as np
import matplotlib.pyplot as plt 

N = 50
dim = (N, N)

init_rand = np.random.random(dim)
lattice = np.zeros(dim)
lattice[init_rand>=0.75] = 1
lattice[init_rand<0.75] = -1

plt.imshow(lattice)
plt.show()